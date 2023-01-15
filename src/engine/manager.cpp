#include "stdafx.h"

namespace local {
#if 0
	EngineManager* __gpEngineManager = nullptr;

	EngineManager::EngineManager() {
	}
	EngineManager::~EngineManager() {
		m_EngineQ.clear();
	}
	Engine* EngineManager::Create(const std::uintptr_t& engineSpi, const int& argc, const char** argv) {
		if (!engineSpi)
			return nullptr;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		auto found = m_EngineQ.find(engineSpi);
		if (found != m_EngineQ.end())
			return found->second;
		return m_EngineQ.emplace(std::make_pair(engineSpi, new Engine(reinterpret_cast<IScriptEngineSpi*>(engineSpi), argc, argv))).first->second;
	}
	bool EngineManager::Destroy(const std::uintptr_t& engineSpi) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		auto found = m_EngineQ.find(engineSpi);
		if (found == m_EngineQ.end())
			return false;
		if (!found->second) {
			m_EngineQ.erase(engineSpi);
			return true;
		}
		found->second->Stop();
		found->second->Release();
		m_EngineQ.erase(engineSpi);
		return true;
	}
#endif



}///namespace local