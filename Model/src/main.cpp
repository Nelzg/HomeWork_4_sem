#include <SFML\Graphics.hpp>
#include <math.h>
#include "../vc2017project/testSFML/testSFML/MaterialPoint.h"
#include <vector>
#include "../vc2017project/testSFML/testSFML/Ball.h"
#include <random>
#include "windows.h"

int GetRandomNumber(int min, int max)
{
    srand(time(NULL));
    int num = min + rand() % (max - min + 1);
    return num;
}

int main()
{

    std::vector<Ball> particles;
    Ball p;

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::Clock clock;

    sf::Texture texture;
    texture.loadFromFile("D:/PROJECTS_INFA/HomeWork_3_sem/Game Project/bin/icon_test.png");
    sf::Sprite circle1(texture);
    circle1.setScale(4, 4);
    int flag_place = 0;
    int flag_count = 0;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Red);

        sf::Time time = clock.getElapsedTime();

        for (int i = 0; i < particles.size(); i++) {
            if (Vector2(sf::Mouse::getPosition(window).x - particles[i].position.x, sf::Mouse::getPosition(window).y - particles[i].position.y).len() <= 100) {
                flag_count++;
            }
            else {
                if (flag_count > 0) {
                    flag_count--;
                }
            }
        }

        if (flag_count == 0) {
            flag_place = 0;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (flag_place == 0)) {
                p.position = Vector2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                p.velocity = Vector2(GetRandomNumber(-2, 2), GetRandomNumber(-2, 2));
                p.mass = 1;//GetRandomNumber(-2, 2);
                p.radius = 50;
                p.circle.setRadius(p.radius);
                p.circle.setOrigin(p.radius, p.radius);
                p.circle.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                particles.push_back(p);
                flag_place = 1;
            }
        }

        for (int i = 0; i + 1 < particles.size(); i++) {
            for (int j = i + 1; j < particles.size(); j++) {
                if ((particles[i].radius + particles[j].radius) > (particles[j].position - particles[i].position).len()) {
                    if ((particles[j].velocity - particles[i].velocity) * (particles[j].position - particles[i].position) < 0) {
                        Vector2 dp = ((particles[j].position - particles[i].position).norm() * ((particles[j].velocity - particles[i].velocity) * (particles[j].position - particles[i].position).norm() / (1 / particles[i].mass + 1 / particles[j].mass)) * 2);
                        particles[i].velocity += dp / particles[i].mass;
                        particles[j].velocity -= dp / particles[j].mass;
                    }
                }
            }
        }
        
        for (int i = 0; i < particles.size(); i++) {
            Vector2 prevPos = particles[i].position;
            if (((750 - particles[i].position.x) <= particles[i].radius)||((particles[i].position.x) <= particles[i].radius)) {
                particles[i].velocity.x = -particles[i].velocity.x;
                particles[i].position = prevPos;
            }
            if (((550 - particles[i].position.y) <= particles[i].radius) || ((particles[i].position.y) <= particles[i].radius)) {
                particles[i].velocity.y = -particles[i].velocity.y;
                particles[i].position = prevPos;
            }
        }


        for (int i = 0; i < particles.size(); i++) {
            particles[i].UpdatePosition(0.01);
            particles[i].circle.setPosition(particles[i].position.x, particles[i].position.y);
            window.draw(particles[i].circle);
        }
        
        
        window.display();
    }

  return 0;
}
