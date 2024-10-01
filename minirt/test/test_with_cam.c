#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_OBJECTS 100
#define MAX_LIGHTS 10

typedef struct { float x, y, z; } Vec3;

typedef enum { SPHERE, PLANE } ObjectType;

typedef struct {
    ObjectType type;
    union {
        struct { Vec3 center; float radius; } sphere;
        struct { Vec3 point; Vec3 normal; } plane;
    };
    Vec3 color;
} Object;

typedef struct { Vec3 origin, direction; } Ray;
typedef struct { Vec3 position; Vec3 color; float intensity; } Light;

// Aktualisierte Kamerastruktur
typedef struct {
    Vec3 position;
    Vec3 direction;
    Vec3 up;
    float fov;
    float aspect_ratio;
} Camera;

// Szene
Object objects[MAX_OBJECTS];
int object_count = 0;
Light lights[MAX_LIGHTS];
int light_count = 0;
Camera camera;

// Vektorfunktionen
Vec3 vec3_create(float x, float y, float z) { return (Vec3){x, y, z}; }
Vec3 vec3_add(Vec3 a, Vec3 b) { return vec3_create(a.x + b.x, a.y + b.y, a.z + b.z); }
Vec3 vec3_subtract(Vec3 a, Vec3 b) { return vec3_create(a.x - b.x, a.y - b.y, a.z - b.z); }
Vec3 vec3_multiply(Vec3 v, float s) { return vec3_create(v.x * s, v.y * s, v.z * s); }
Vec3 vec3_multiply_components(Vec3 a, Vec3 b) { return vec3_create(a.x * b.x, a.y * b.y, a.z * b.z); }
float vec3_dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
float vec3_length(Vec3 v) { return sqrt(vec3_dot(v, v)); }
Vec3 vec3_normalize(Vec3 v) { return vec3_multiply(v, 1.0f / vec3_length(v)); }
Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return vec3_create(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

// Objekte zur Szene hinzufügen
void add_sphere(Vec3 center, float radius, Vec3 color) {
    if (object_count < MAX_OBJECTS) {
        objects[object_count].type = SPHERE;
        objects[object_count].sphere.center = center;
        objects[object_count].sphere.radius = radius;
        objects[object_count].color = color;
        object_count++;
    }
}

void add_plane(Vec3 point, Vec3 normal, Vec3 color) {
    if (object_count < MAX_OBJECTS) {
        objects[object_count].type = PLANE;
        objects[object_count].plane.point = point;
        objects[object_count].plane.normal = vec3_normalize(normal);
        objects[object_count].color = color;
        object_count++;
    }
}

void add_light(Vec3 position, Vec3 color, float intensity) {
    if (light_count < MAX_LIGHTS) {
        lights[light_count].position = position;
        lights[light_count].color = color;
        lights[light_count].intensity = intensity;
        light_count++;
    }
}

// Neue Kamera-Erstellungsfunktion
Camera create_camera(Vec3 position, Vec3 look_at, float fov, float aspect_ratio) {
    Camera cam;
    cam.position = position;
    cam.direction = vec3_normalize(vec3_subtract(look_at, position));
    // Temporärer "up" Vektor
    Vec3 temp_up = vec3_create(0, 1, 0);
    // Berechne den "right" Vektor
    Vec3 right = vec3_normalize(vec3_cross(cam.direction, temp_up));
    // Berechne den endgültigen "up" Vektor
    cam.up = vec3_normalize(vec3_cross(right, cam.direction));
    cam.fov = fov;
    cam.aspect_ratio = aspect_ratio;
    return cam;
}

// Aktualisierte Funktion zum Erzeugen eines Strahls von der Kamera
Ray get_ray(float u, float v) {
    float theta = camera.fov * M_PI / 180.0;
    float half_height = tan(theta / 2);
    float half_width = camera.aspect_ratio * half_height;
    
    Vec3 w = vec3_multiply(camera.direction, -1);
    Vec3 u_axis = vec3_normalize(vec3_cross(camera.up, w));
    Vec3 v_axis = vec3_cross(w, u_axis);

    Vec3 lower_left_corner = vec3_subtract(camera.position,
                                           vec3_add(vec3_multiply(u_axis, half_width),
                                                    vec3_add(vec3_multiply(v_axis, half_height),
                                                             w)));
    Vec3 horizontal = vec3_multiply(u_axis, 2 * half_width);
    Vec3 vertical = vec3_multiply(v_axis, 2 * half_height);

    Vec3 direction = vec3_normalize(vec3_subtract(
        vec3_add(lower_left_corner,
                 vec3_add(vec3_multiply(horizontal, u),
                          vec3_multiply(vertical, v))),
        camera.position));

    return (Ray){camera.position, direction};
}

// Schnittpunktberechnungen
int intersect_sphere(Ray ray, Vec3 center, float radius, float* t) {
    Vec3 oc = vec3_subtract(ray.origin, center);
    float a = vec3_dot(ray.direction, ray.direction);
    float b = 2.0f * vec3_dot(oc, ray.direction);
    float c = vec3_dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) return 0;
    float t0 = (-b - sqrt(discriminant)) / (2.0f * a);
    float t1 = (-b + sqrt(discriminant)) / (2.0f * a);
    *t = (t0 < t1) ? t0 : t1;
    return *t > 0;
}

int intersect_plane(Ray ray, Vec3 point, Vec3 normal, float* t) {
    float denom = vec3_dot(ray.direction, normal);
    if (fabs(denom) > 1e-6) {
        Vec3 p0l0 = vec3_subtract(point, ray.origin);
        *t = vec3_dot(p0l0, normal) / denom;
        return (*t >= 0);
    }
    return 0;
}

int is_in_shadow(Vec3 point, Vec3 light_dir, float light_distance) {
    Ray shadow_ray = {point, light_dir};
    float t;
    for (int i = 0; i < object_count; i++) {
        switch (objects[i].type) {
            case SPHERE:
                if (intersect_sphere(shadow_ray, objects[i].sphere.center, objects[i].sphere.radius, &t) && t < light_distance)
                    return 1;
                break;
            case PLANE:
                if (intersect_plane(shadow_ray, objects[i].plane.point, objects[i].plane.normal, &t) && t < light_distance)
                    return 1;
                break;
        }
    }
    return 0;
}

Vec3 ray_color(Ray ray) {
    float closest_t = INFINITY;
    int closest_object = -1;
    float t;

    for (int i = 0; i < object_count; i++) {
        switch (objects[i].type) {
            case SPHERE:
                if (intersect_sphere(ray, objects[i].sphere.center, objects[i].sphere.radius, &t) && t < closest_t) {
                    closest_t = t;
                    closest_object = i;
                }
                break;
            case PLANE:
                if (intersect_plane(ray, objects[i].plane.point, objects[i].plane.normal, &t) && t < closest_t) {
                    closest_t = t;
                    closest_object = i;
                }
                break;
        }
    }

    if (closest_object != -1) {
        Vec3 hit_point = vec3_add(ray.origin, vec3_multiply(ray.direction, closest_t));
        Vec3 normal;
        
        switch (objects[closest_object].type) {
            case SPHERE:
                normal = vec3_normalize(vec3_subtract(hit_point, objects[closest_object].sphere.center));
                break;
            case PLANE:
                normal = objects[closest_object].plane.normal;
                break;
        }

        Vec3 color = {0, 0, 0};
        for (int i = 0; i < light_count; i++) {
            Vec3 light_dir = vec3_subtract(lights[i].position, hit_point);
            float light_distance = vec3_length(light_dir);
            light_dir = vec3_normalize(light_dir);

            if (!is_in_shadow(vec3_add(hit_point, vec3_multiply(normal, 0.001)), light_dir, light_distance)) {
                float diffuse = fmaxf(vec3_dot(normal, light_dir), 0.0f);
                Vec3 diffuse_color = vec3_multiply_components(objects[closest_object].color, lights[i].color);
                color = vec3_add(color, vec3_multiply(diffuse_color, diffuse * lights[i].intensity));
            }
        }

        Vec3 ambient_color = vec3_multiply(objects[closest_object].color, 0.1f);
        return vec3_add(color, ambient_color);
    }

    // Hintergrundfarbe (Himmel)
    Vec3 unit_direction = vec3_normalize(ray.direction);
    float t_background = 0.5f * (unit_direction.y + 1.0f);
    Vec3 white = vec3_create(1.0f, 1.0f, 1.0f);
    Vec3 blue = vec3_create(0.5f, 0.7f, 1.0f);
    return vec3_add(vec3_multiply(white, 1.0f - t_background), vec3_multiply(blue, t_background));
}

int main() {
    int width = 800;
    int height = 600;

    // Kamera initialisieren mit der neuen Funktion
    camera = create_camera(vec3_create(0, 0, 0), vec3_create(0, 0, -1), 90, (float)width / height);

    // Szene erstellen
    add_sphere(vec3_create(0, 0, -3), 1, vec3_create(1, 0, 0));    // Rote Kugel
    add_sphere(vec3_create(-2, 0, -4), 1, vec3_create(0, 1, 0));   // Grüne Kugel
    add_sphere(vec3_create(2, 0, -4), 1, vec3_create(0, 0, 1));    // Blaue Kugel
    add_plane(vec3_create(0, -1, 0), vec3_create(0, 1, 0), vec3_create(0.5, 0.5, 0.5)); // Graue Ebene
    add_light(vec3_create(0, 5, 0), vec3_create(1, 1, 1), 1.0f);   // Weißes Licht von oben

    printf("P3\n%d %d\n255\n", width, height);

    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            float u = (float)i / (width - 1);
            float v = (float)j / (height - 1);
            
            Ray ray = get_ray(u, v);
            Vec3 color = ray_color(ray);
            
            int ir = (int)(255.99 * fminf(color.x, 1.0f));
            int ig = (int)(255.99 * fminf(color.y, 1.0f));
            int ib = (int)(255.99 * fminf(color.z, 1.0f));
            
            printf("%d %d %d\n", ir, ig, ib);
        }
    }

    return 0;
}