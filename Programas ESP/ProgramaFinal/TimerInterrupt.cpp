#include "TimerInterrupt.h"
#include <math.h>

// Initialize the static variables
volatile SemaphoreHandle_t TimerInterrupt::timerSemaphore = xSemaphoreCreateBinary();

TimerInterrupt::TimerInterrupt(SaveToFlash *files, Communicator *communicator)
{
  timer = NULL;
  QtdMinutes = 1; // Default time is 60 minutes
  this->fileSystem = files;
  this->communicator = communicator;
}

void IRAM_ATTR TimerInterrupt::onTimer()
{                                              // It is safe to use digitalRead/Write here if you want to toggle an output
  xSemaphoreGiveFromISR(timerSemaphore, NULL); // Give a semaphore that we can check in the loop
}

void TimerInterrupt::timer_init()
{
  // Use 1st timer of 4 (counted from zero).
  // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more info).
  timer = timerBegin(0, 80, true);

  timerAttachInterrupt(timer, &TimerInterrupt::onTimer, true); // Attach onTimer function to our timer.

  int SetTime = QtdMinutes * 10 * 1000000; // Set alarm to call onTimer function every QtdMinutes
  timerAlarmWrite(timer, SetTime, true);   // Repeat the alarm (third parameter)

  timerAlarmEnable(timer); // Start an alarm
}

bool TimerInterrupt::tryToSendCacheToServer()
{
  bool sent = true;
  int qtd_cache = this->fileSystem->getNCacheSaves();
  int pages = ceil((float)qtd_cache / (float)NUM_READINGS);

  this->communicator->reconnect_client(); // chama isso pra acordar o cliente e reconectar com o broker -> só funciona se o esp estiver em modo client
  for (int i = 0; i < pages; i++)
  {
    Readings_Lists readings = this->fileSystem->get_readings_from_cache(i);
    if (!(this->communicator->send_data_to_server(readings)))
    {
      sent = false;
      break;
    }
  }
  this->communicator->sleep();
  return sent;
}

void TimerInterrupt::timer_interruption()
{ // If Timer has fired
  String time = DateTime.toISOString().c_str();
  float BatteryCurrent = 2.0, BatteryVoltage = 30.9, PVCurrent = 11.1, PVVoltage = 9.876;
  if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE)
  {
    Serial.println("entering timer interrupt");

    // Read the sensors

    fileSystem->saveToCache(time, BatteryCurrent, BatteryVoltage, PVCurrent);
    int n_cache_saves = fileSystem->getNCacheSaves();
    int cache_size = fileSystem->getCachesize();
    // If the cache is full, save it to the long term memory
    Serial.printf("n_cache: %d | cache_size: %d\n", n_cache_saves, cache_size);
    if (n_cache_saves >= cache_size && this->tryToSendCacheToServer())
    {
      fileSystem->saveToLongTerm();
    }
    //    Readings_Lists readings = fileSystem->get_readings_/from_cache(0);
  }
}

void TimerInterrupt::set_newtime(int newTime)
{
  QtdMinutes = newTime;
}
