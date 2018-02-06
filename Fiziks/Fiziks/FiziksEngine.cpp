#include "FiziksEngine.h"

FiziksEngine::FiziksEngine()
{
	m_timer = new sf::Clock();
	m_delta_timer = new sf::Clock();

	// TODO: No longer hardcode this
	KinematicsEntity* exp_euler_entity = new KinematicsEntity(ExplicitEuler);
	KinematicsEntity* imp_euler_entity = new KinematicsEntity(SemiImplicitEuler);
	KinematicsEntity* uni_entity = new KinematicsEntity(UniformAcceleration);
	KinematicsEntity* proj_entity = new KinematicsEntity(ProjectileMotion);

	m_entities.push_back(exp_euler_entity);
	m_entities.push_back(imp_euler_entity);
	m_entities.push_back(uni_entity);
	m_entities.push_back(proj_entity);
}

FiziksEngine::~FiziksEngine()
{
	for (int i = 0; i < m_entities.size(); i++) {
		delete m_entities[i];
		m_entities[i] = nullptr;
	}

	delete m_timer;
	m_timer = nullptr;
	delete m_delta_timer;
	m_delta_timer = nullptr;
}

void FiziksEngine::update()
{
	// Record total time passed in simulation and time since last frame
	sf::Time* total_time = &m_timer->getElapsedTime();
	sf::Time* delta_time = &m_delta_timer->restart();

	for (Entity* e : m_entities) {
		e->update(total_time, delta_time);
	}
}

void FiziksEngine::draw(sf::RenderWindow* window)
{
	for (Entity* e : m_entities) {
		e->draw(window);
	}

	// TODO: Remove this
	// Displays all of the different Kinematics objects' positions
	//std::ostringstream oss;
	//sf::Text screen_text = sf::Text();
	//screen_text.setFont(sf::Font::)
	//sf::String text;

	//oss << m_entities[0]->get_pos().x;
	//text = sf::String((std::string)oss.str());

	///*for (Entity* e : m_entities) {
	//	text.insert(text.getSize() - 1, ")\n");
	//	oss << e->get_pos().x;
	//	text.insert(text.getSize() - 1, oss.str());
	//	text.insert(text.getSize() - 1, ", ");
	//	oss << e->get_pos().y;
	//	text.insert(text.getSize() - 1, ")\n");
	//}*/

	//screen_text.setString(text);
	//screen_text.setCharacterSize(30);
	//screen_text.setFillColor(sf::Color::White);

	//window->draw(screen_text);
}