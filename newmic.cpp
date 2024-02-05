#include <iostream>
#include <SFML/Audio.hpp>


int main()
{
	// Создание объекта записи
	sf::SoundBufferRecorder recorder;

	// Начать запись
	recorder.start();
	char name[2];
	std::cout << "Recording... Press Enter to stop" << std::endl;
	std::cin.get(name,sizeof(name));

	// Остановить запись
	recorder.stop();

	// Получить буфер записанного звука
	const sf::SoundBuffer& buffer = recorder.getBuffer();

	char* temporaryPath = nullptr;
	size_t len;
	errno_t err = _dupenv_s(&temporaryPath, &len, "TMP");

	if (err == 0 && temporaryPath != NULL)
	{
		std::string filePath = std::string(temporaryPath) + "\\recorded_sound.wav";

		// Сохранить звук в файл
		if (buffer.saveToFile(filePath))
		{
			std::cout << "Recording saved to " << filePath << std::endl;
		}
		else
		{
			std::cerr << "Failed to save recording" << std::endl;
		}
		free(temporaryPath);
	}
	else
	{
		std::cerr << "Failed to get temporary directory path" << std::endl;
	}

	return 0;
}