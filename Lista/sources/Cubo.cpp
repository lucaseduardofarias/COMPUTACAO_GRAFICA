#include "../headers/Cubo.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX;
float lastY;
bool firstMouse = true;
Camera* _camera;

Cubo::Cubo(int width, int height, std::string screenTitle) {
    this->WIDTH = width;
    this->HEIGHT = height;
    this->SCREEN_TITLE = screenTitle;
    lastX = (float)this->WIDTH / 2.0f;
    lastY = (float)this->HEIGHT / 2.0f;
    _camera = this->camera;
}

Cubo::~Cubo() {}

Face* createFace(int v0, int v1, int v2, int v3, int normal) {
    Face* face = new Face();
    face->addVerticeId(v0);
    face->addVerticeId(v1);
    face->addVerticeId(v3);

    face->addVerticeId(v1);
    face->addVerticeId(v2);
    face->addVerticeId(v3);
    return face;
}

int Cubo::init(GLFWwindow* window) {

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    this->mesh = new Mesh();
    int A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7;
    float escale = 2;

    this->mesh->addVertice(new glm::vec3(1.0f / escale, 1.0f / escale, 1.0f / escale)); //A
    this->mesh->addVertice(new glm::vec3(-1.0f / escale, 1.0f / escale, 1.0f / escale)); //B
    this->mesh->addVertice(new glm::vec3(-1.0f / escale, -1.0f / escale, 1.0f / escale)); //C
    this->mesh->addVertice(new glm::vec3(1.0f / escale, -1.0f / escale, 1.0f / escale)); //D      
    this->mesh->addVertice(new glm::vec3(1.0f / escale, 1.0f / escale, -1.0f / escale)); //E
    this->mesh->addVertice(new glm::vec3(-1.0f / escale, 1.0f / escale, -1.0f / escale)); //F
    this->mesh->addVertice(new glm::vec3(-1.0f / escale, -1.0f / escale, -1.0f / escale)); //G
    this->mesh->addVertice(new glm::vec3(1.0f / escale, -1.0f / escale, -1.0f / escale)); //H

    Group* group = new Group();
    group->addFace(createFace(A, B, C, D, 4));
    group->addFace(createFace(A, D, H, E, 0));
    group->addFace(createFace(A, E, F, B, 2));
    group->addFace(createFace(C, B, F, G, 1));
    group->addFace(createFace(D, C, G, H, 3));
    group->addFace(createFace(H, G, F, E, 5));


    this->mesh->addGroup(group);
    this->mesh->setShader(new Shader("./shaders/core/vertex.vert", "./shaders/core/fragment.frag"));
    this->mesh->setShaderColor(new Shader("./shaders/core/vertex.vert", "./shaders/core/fragment_color.frag"));

    glm::ortho(0.0f, (float)this->WIDTH, 0.0f, (float)this->HEIGHT, 0.1f, 100.0f);

    this->cubePositions.push_back(new glm::vec3(3.0f, 2.0f, 0.0f));



    for (Group* group : this->mesh->getGroups()) {
        vector<float> vertices;

        for (Face* face : group->getFaces()) {
            for (int verticeID : face->getVertices()) {
                glm::vec3* vertice = this->mesh->vertice(verticeID);
                vertices.push_back(vertice->x);
                vertices.push_back(vertice->y);
                vertices.push_back(vertice->z);
            }
        }

        GLuint VAO, VBOvert;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBOvert);

        glBindBuffer(GL_ARRAY_BUFFER, VBOvert);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        glEnableVertexAttribArray(0);

        group->setVAO(&VAO);
        group->addVBO(&VBOvert);
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    return EXIT_SUCCESS;
}

void Cubo::run(GLFWwindow* window) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(camera->zoom), (float)this->WIDTH / (float)this->HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera->getViewMatrix();

    for (int i = 0; i < cubePositions.size(); i++) {
        glm::vec3 cubePosition = *cubePositions[i];
        glm::mat4 model(1.0f);
        model = glm::translate(model, cubePosition);


        this->mesh->getShader()->use();
        for (Group* group : this->mesh->getGroups()) {
            this->mesh->getShader()->setMatrix4fv("model", model);
            this->mesh->getShader()->setMatrix4fv("view", view);
            this->mesh->getShader()->setMatrix4fv("projection", projection);
            glBindVertexArray(group->getVAO());
            glDrawArrays(GL_TRIANGLES, 0, group->numVertices());
        }

        this->mesh->getShaderColor()->use();
        for (Group* group : this->mesh->getGroups()) {
            this->mesh->getShaderColor()->setMatrix4fv("model", model);
            this->mesh->getShaderColor()->setMatrix4fv("view", view);
            this->mesh->getShaderColor()->setMatrix4fv("projection", projection);
            glBindVertexArray(group->getVAO());
            glDrawArrays(GL_LINE_LOOP, 0, group->numVertices());
        }

    }

}

bool Cubo::keepRunning(GLFWwindow* window) {
    return !glfwWindowShouldClose(window);
}

void Cubo::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        _camera->processKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        _camera->processKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        _camera->processKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        _camera->processKeyboard(RIGHT, deltaTime);
    }
}


void Cubo::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    _camera->processMouseMovement(xoffset, yoffset);
}

void Cubo::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Cubo::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    _camera->processMouseScroll(yoffset);
}

void Cubo::finish() {
    delete this->mesh;
}

int Cubo::width() {
    return this->WIDTH;
}

int Cubo::height() {
    return this->HEIGHT;
}

std::string Cubo::screenTitle() {
    return this->SCREEN_TITLE;
}
