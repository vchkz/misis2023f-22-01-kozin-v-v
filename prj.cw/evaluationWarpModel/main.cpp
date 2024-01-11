#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include "image.h"
#include "imageEval.h"

#define M_PI 3.14159265358979323846

enum screenState {
    mainScreen = 0,
    DistortionEvaluationScreen
} currentState;


struct App {
    sf::RenderWindow window;

    sf::Vector2f translate;
    sf::Vector2f mouseCoord;

    Image firstIm;
    Image secondIm;

    ImageEval evaluationImg;


    bool showEvaluationSettingsWindow = false;


    float zoom;

    enum distortImage {
        firstImage = 0,
        secondImage
    } currentDistortImage = firstImage;

    App() : window(sf::VideoMode(1800, 900), "AstMarker"), zoom(1.0f) {

        evaluationImg.internalTexture.create(window.getSize().x, window.getSize().y);
        evaluationImg.pointsTexture.create(window.getSize().x, window.getSize().y);

    }

    void updateTextures() {
        if (currentDistortImage == firstImage) {
            evaluationImg.drawPicture(secondIm.sprite);
            evaluationImg.drawEvalPoints(secondIm.ast);
        }
        if (currentDistortImage == secondImage) {
            evaluationImg.drawPicture(firstIm.sprite);
            evaluationImg.drawEvalPoints(firstIm.ast);
        }
    }


    void handleInput() {
        sf::Event event;

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                evaluationImg.pointsTexture.create(window.getSize().x, window.getSize().y);
                evaluationImg.internalTexture.create(window.getSize().x, window.getSize().y);
                updateTextures();


            } else if (event.type == sf::Event::MouseWheelScrolled) { // Масштабирование колёсиком мыши

                sf::Vector2f newCoord = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                float delta = event.mouseWheelScroll.delta;
                float scaleFactor = 1.0f + delta * 0.1f;
                float oldZoom = zoom;

                zoom *= scaleFactor;
                translate += (newCoord - translate) - (newCoord - translate) * (zoom / oldZoom);

                evaluationImg.sprite.setScale(zoom, zoom);
                evaluationImg.sprite.setPosition(translate);
                updateTextures();

            } else if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f newCoord(event.mouseMove.x, event.mouseMove.y);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    translate += newCoord - mouseCoord;
                    evaluationImg.sprite.setPosition(translate);

                    updateTextures();
                }
                mouseCoord = newCoord;
            }
        }
    }


    void update() {
        ImGui::SFML::Update(window, sf::seconds(1.0f / 60.0f));
        if (ImGui::BeginMainMenuBar()) {

            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open Image 1")) {
                    firstIm.openImage();
                }
                if (ImGui::MenuItem("Open Image 2")) {
                    secondIm.openImage();
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Import 1st Image Points", nullptr, false, true)) {
                    firstIm.importPoints();
                }
                if (ImGui::MenuItem("Import 2nd Image Points", nullptr, false, true)) {
                    secondIm.importPoints();
                };
                if (ImGui::MenuItem("Quit")) {
                    window.close();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Warp evaluation")) {
                if (ImGui::MenuItem("Warp image", nullptr, false, firstIm.ast.countPts() > 3)) {
                    currentState = DistortionEvaluationScreen;
                    evaluationImg.genEvalImg(firstIm, secondIm);
                    evaluationImg.drawPicture(secondIm.sprite);
                    showEvaluationSettingsWindow = true;
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", nullptr, false, currentState == DistortionEvaluationScreen)) {
                    currentState = mainScreen;
                    showEvaluationSettingsWindow = false;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }


        ImGui::SetNextWindowPos(ImVec2(window.getSize().x - 300.0f, 30.0f), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(300.0f, 300.0f), ImGuiCond_Once);

        ImGui::Begin("Model Settings", &showEvaluationSettingsWindow);

        ImGui::Separator();
        ImGui::Text("Type of transformation:");
        if (ImGui::RadioButton("Affine", (int *) &evaluationImg.currentModelType, evaluationImg.affine)) {
            if (currentDistortImage == firstImage) { evaluationImg.genEvalImg(firstIm, secondIm); }
            if (currentDistortImage == secondImage) { evaluationImg.genEvalImg(secondIm, firstIm); }
        }
        ImGui::SameLine();
        if (ImGui::RadioButton("Perspective", (int *) &evaluationImg.currentModelType, evaluationImg.perspective)) {
            if (currentDistortImage == firstImage) { evaluationImg.genEvalImg(firstIm, secondIm); }
            if (currentDistortImage == secondImage) { evaluationImg.genEvalImg(secondIm, firstIm); }
        }
        ImGui::Separator();
        ImGui::Text("Which image should be warped:");
        if (ImGui::RadioButton("First", (int *) &currentDistortImage, firstImage)) {
            evaluationImg.genEvalImg(firstIm, secondIm);
            evaluationImg.drawPicture(secondIm.sprite);
        }
        ImGui::SameLine();
        if (ImGui::RadioButton("Second", (int *) &currentDistortImage, secondImage)) {
            evaluationImg.genEvalImg(secondIm, firstIm);
            evaluationImg.drawPicture(firstIm.sprite);
        }

        ImGui::Separator();
        if (ImGui::Checkbox("Show points", &evaluationImg.showPoints))updateTextures();
        if (ImGui::SliderFloat("Line wight", &evaluationImg.lineWidth, 1.0f, 20.0f))updateTextures();
        ImGui::End();


        ImGui::Begin("edit", nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        {
            ImGui::SetWindowPos(ImVec2(0.0f, window.getSize().y - 30.0f));
            ImGui::SetWindowSize(ImVec2(window.getSize().x, 30.0f));
            ImGui::Columns(4);
            if (ImGui::SliderFloat("Point width", &Image::pointRadius, 1.0f, 20.0f)) updateTextures();
            ImGui::NextColumn();
            if (ImGui::SliderFloat("Transparency", &Image::transparency, 0.0f, 1.0f)) updateTextures();

        }
        ImGui::End();


    }

    void render() {
        window.clear();
        sf::Sprite internalSprite;
        sf::Sprite internalPointSprite;
        internalSprite.setTexture(evaluationImg.internalTexture.getTexture());
        internalPointSprite.setTexture(evaluationImg.pointsTexture.getTexture());

        evaluationImg.internalTexture.display();
        window.draw(internalSprite);

        evaluationImg.pointsTexture.display();
        window.draw(internalPointSprite);
        ImGui::SFML::Render(window);
        window.display();
    }

    void run() {
        ImGui::SFML::Init(window);
        while (window.isOpen()) {
            handleInput();
            update();
            render();

        }
        ImGui::SFML::Shutdown();
    }
};

int main() {
    App app;
    app.run();

    return 0;
}
