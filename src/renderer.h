extern const unsigned int TYPE_TRIANGLE;
extern const unsigned int TYPE_RECTANGLE;

unsigned int vbo, vao, ebo;

void begin_triangle(float* vertices, unsigned int size, int vertex_shader, int fragment_shader);
void begin_rectangle(float* vertices, unsigned int vertices_size, unsigned int* indices, unsigned int indices_size, int vertex_shader, int fragment_shader);

void render(const unsigned int shape);