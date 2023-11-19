#include "communicator.h"
// class Sensors
// {
// };

// class BatteryController
// {
// };

// class FileSystem
// {
// };

// class TimerInterrupt
// {
// };

// Cria as instancias globais das classes
Communicator communicator;

void setup()
{
    Serial.begin(9600);

    // faz as configurações iniciais de cada objeto, dos attach dos interrupts
    communicator.init();

    // verifica o tempo da rede (fica travado aqui até ele conseguir pegar o tempo inicial pra fazer as coisas)
    // ou seja, antes daqui tando o PWM quanto o switch do Load tem que estar abertos para não dar problema, pq o esp vai ficar travado aqui
    Serial.println("Verificando o tempo da rede");
    communicator.setup_datetime();
    Serial.println(DateTime.toString());
}

bool envio = true;

void loop()
{

    // chama a função de verificar flags do comunicador
    communicator.interrupt_handler();

    if (communicator.is_server)
    {
        //   Serial.println("é server");
        communicator.run_server();
        envio = true;
    }
    else
    {

        if (envio)
        {

            communicator.reconnect_client(); // chama isso pra acordar o cliente e reconectar com o broker -> só funciona se o esp estiver em modo client
            if (communicator.send_data_to_server(JSON_SOLAR_BAT_CURRENT, 40.44, DateTime.toISOString()))
            {
                Serial.println("Enviado com sucesso");
                envio = false;
                communicator.sleep(); // chama isso pra botar pra dormir -> isso aqui desliga o AP tb, então cuidado
            }
            else
            {
                Serial.println("Não foi enviado");
            }
        }
    }

    // if( not comunidaor.isServer)
    // verifica o counter do TimerInterrupt e faz as chamadas
    // timer_interruption(fileSystem, Sensors, comunicator) // -> faz as verificações de tempo e levanta as flags de processos

    // chama a função de controle da bateria
    // battery_loop(sensors)
    delay(500);
}
