#include "observer.h"

observer::observer(fiziks_engine* engine)
{
	if (engine == NULL) {
		m_engine = engine;
	}
	m_engine->attach(this);
}