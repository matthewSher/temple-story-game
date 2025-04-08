#pragma once

#include <string>

/**
 * Функции для логирования сообщений об ошибках и информационных сообщений.
 * Эти функции могут использоваться для отладки и отслеживания состояния программы.
 */

// Логирование ошибок
void errorLog(const std::string& funcName, const std::string& error);
// Логирование информационных сообщений
void infoLog(const std::string& funcName, const std::string& info);