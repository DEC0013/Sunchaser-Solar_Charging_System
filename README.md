# Sunchaser-Solar_Charging_System: Controle de Carga PWM com ESP32 e Placa Fotovoltaica

## Introdução

Este projeto foi desenvolvido como parte de um sistema ubíquo para o controle eficiente da carga de baterias de chumbo-ácido ou de lítio, utilizando uma placa fotovoltaica de 20W. O sistema emprega uma metodologia de modulação de largura de pulso (PWM) controlada por um ESP32 para regular a tensão e a corrente fornecida pela placa solar, assegurando uma tensão estável na bateria. Os dados de carregamento são monitorados e transmitidos para um Broker MQTT, integrando-se ao projeto do Pluviômetro existente. Adicionalmente, um aplicativo móvel fornece acesso local aos dados através de uma API REST.

O projeto é dividido em várias etapas de desenvolvimento, com testes dedicados para cada componente, seguindo princípios de orientação a objetos. Esta documentação fornece uma visão detalhada da estrutura do projeto, descrições de hardware e software, além de instruções operacionais e de diagnóstico.

## Descrição do Projeto

O sistema é projetado para operar em locais remotos, onde a estabilidade da conexão de internet pode ser intermitente. Portanto, ele armazena dados localmente e tenta transmitir informações retroativas quando uma conexão está disponível. A abordagem de design permite o acesso local aos dados do ESP32, que pode alternar entre modos cliente e servidor para facilitar a interação com o usuário por meio de um aplicativo móvel.

### Objetivos

- Manter uma tensão estável de 12V na bateria, conforme especificações técnicas do fabricante.
- Monitorar e armazenar dados de corrente e tensão para análises de longo prazo.
- Permitir o acesso local aos dados via aplicativo móvel para monitoramento e controle.
- Transmitir dados acumulados para um sistema centralizado quando conectado à internet.

Continue lendo para uma visão detalhada da implementação do projeto, incluindo instruções de montagem de hardware, configuração de software, e operação do sistema.

## Estrutura de Arquivos

O projeto está organizado em diretórios que separam cada componente e fase de desenvolvimento, facilitando a navegação e compreensão do sistema como um todo. Abaixo está a árvore de arquivos com a descrição de cada diretório e arquivo-chave:

```
.
├── App Mobile # Código fonte e recursos para o aplicativo móvel.
│ ├── mobile
│ │ ├── App.js # Ponto de entrada do aplicativo React Native.
│ │ └── (restante da estrutura do diretório do aplicativo)
├── Documentação # Documentos de planejamento, relatórios e artigos de referência.
│ ├── Cronograma
│ │ └── (imagens do cronograma)
│ ├── Diagramas
│ │ └── (diagramas e fluxogramas do projeto)
│ └── (restante da documentação)
├── logo # Recursos gráficos e logotipos do projeto.
├── Placa de Controle # Projeto do hardware no Proteus e imagens associadas.
│ ├── Controle de Carga PWM
│ │ └── (arquivos do Proteus e backups)
│ └── (restante dos diretórios de hardware)
├── Programas ESP # Códigos para o ESP32, incluindo exemplos de teste e o programa final.
│ ├── Desenvolvimento
│ │ └── (exemplos de teste)
│ ├── ProgramaFinal # Código-fonte final que será executado no ESP32.
│ │ └── (arquivos .cpp e .h do programa final)
│ └── (restante dos programas e bibliotecas)
└── README.md # Este documento de README.
```

## Configuração de Hardware

### Componentes

- ESP32: Microcontrolador central que gerencia a comunicação e o controle PWM.
- Placa Fotovoltaica de 20W: Fornece energia solar convertida para carregar a bateria.
- Bateria de Chumbo-Ácido ou Lítio: Armazena a energia gerada pelo painel solar.
- INA219: Sensores de corrente para monitoramento da carga e descarga da bateria.
- MOSFET Canal P: Atua como um interruptor controlado por PWM para regular a tensão do painel solar.

### Montagem

Os componentes devem ser montados de acordo com os diagramas fornecidos na pasta `Placa de Controle`. É crucial verificar e testar todas as conexões antes de energizar o circuito para evitar danos aos componentes.

### Notas Sobre o Proteus

O projeto foi desenvolvido utilizando o Proteus 8.9. Versões mais recentes são capazes de abrir o projeto, mas versões anteriores não. Salvar o projeto em uma versão mais nova resultará em incompatibilidade com a 8.9.

## Configuração de Software

### Ambiente de Desenvolvimento

O código-fonte foi desenvolvido na Arduino IDE, uma plataforma de desenvolvimento que permite a escrita, compilação e upload de programas para placas compatíveis com Arduino, como o ESP32 utilizado neste projeto.

### Instalação

1. Instale a última versão da Arduino IDE a partir do [site oficial](https://www.arduino.cc/en/software).
2. Configure a Arduino IDE para suportar o ESP32 seguindo as instruções disponíveis na [documentação do ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).
3. Instale todas as bibliotecas necessárias mencionadas nos arquivos `package.json` e `yarn.lock` localizados na pasta `App Mobile/mobile`.

### Descrição dos Programas de Teste

Os programas de teste localizados em `Programas ESP/Desenvolvimento` são fundamentais para validar o funcionamento individual de cada componente do sistema. Cada subdiretório contém um exemplo de código que pode ser compilado e carregado separadamente para testar sensores, comunicação, controle PWM, entre outros.

### Programa Final

A pasta `Programas ESP/ProgramaFinal` contém o código-fonte consolidado que será executado no ESP32. Inclui a integração das classes desenvolvidas, a lógica de controle PWM e a comunicação com o Broker MQTT.

### Documentação do Código

O código deve ser documentado detalhadamente, descrevendo a função de cada método e classe. Especial atenção deve ser dada aos módulos de comunicação, que detalham a interação com o aplicativo móvel e o Broker MQTT.

ado que será executado no ESP32. Este diretório é o coração do software do projeto, integrando todas as funcionalidades e classes necessárias para o sistema operar de maneira autônoma e eficiente.

#### Arquivos Principais

- `ProgramaFinal.ino`: Arquivo principal do programa que inclui a lógica de inicialização e o loop de execução.
- `BatteryControl.cpp` e `BatteryControl.h`: Definem a classe responsável pelo controle da carga da bateria.
- `Sensors.cpp` e `Sensors.h`: Incluem as definições para leitura dos sensores INA219 e medição de tensão e corrente.
- `TimerInterrupt.cpp` e `TimerInterrupt.h`: Gerenciam as interrupções de tempo para operações periódicas.
- `SaveToFlash.cpp` e `SaveToFlash.h`: Permitem a gravação e recuperação de dados na memória flash do ESP32.
- `communicator.cpp` e `communicator.h`: Contêm a lógica para a comunicação entre o ESP32 e o Broker MQTT ou o aplicativo móvel.

#### Operação do Programa

O `ProgramaFinal.ino` executa as seguintes tarefas principais:

1. Conexão à rede Wi-Fi e sincronização de horário para timestamp dos dados.
2. Inicialização dos módulos de controle de carga e sensores.
3. Loop principal de controle da tensão da bateria, onde o PWM é ajustado para manter a tensão desejada.
4. Leitura periódica dos dados de corrente e tensão, salvando no cache local a cada intervalo definido.
5. Tentativa de envio de dados acumulados ao Broker MQTT e transferência para memória de longo prazo em caso de sucesso.
6. Alternância entre modos cliente e servidor para permitir o acesso local via aplicativo móvel.

### Documentação das APIs

A comunicação com o ESP32 pode ser realizada através das seguintes APIs, disponíveis quando o ESP está em modo servidor:

| Operação | Rota      | Query Params  | Body                      | Retorno                                                                   | Observações                                           |
| -------- | --------- | ------------- | ------------------------- | ------------------------------------------------------------------------- | ----------------------------------------------------- |
| GET      | /cache    | page: Numeric | -                         | JSON: Lista de leituras do cache, total de itens, itens por página (10)   | Máximo de 10 itens por página                         |
| GET      | /ltm      | page: Numeric | -                         | JSON: Lista de leituras da memória, total de itens, itens por página (10) | Máximo de 10 itens por página                         |
| POST     | /reading  | -             | -                         | JSON: Novas medições                                                      | -                                                     |
| POST     | /settings | -             | JSON: Novas configurações | -                                                                         | O app verifica o sucesso pela resposta do status code |
| GET      | /settings | -             | -                         | JSON: Configurações atuais                                                | -                                                     |
| GET      | /check    | -             | -                         | String: "conectado!"                                                      | Utilizado para verificar a conexão com o ESP          |

### Diagnóstico de Problemas e Soluções

Durante o desenvolvimento, foram identificados e solucionados diversos desafios:

- **Problema de Versão do Proteus**: Limitação da versão 8.9 do Proteus para salvar e abrir arquivos sem perder a compatibilidade.
- **Comportamento Inesperado de Tensões**: Solucionado com a inclusão de uma resistência em paralelo à fonte de bancada.
- **Limitações dos ADCs do ESP32**: Ajustes nas leituras analógicas para evitar conflitos entre o ADC2 e o uso do Wi-Fi e erros causados por tensões altas nos pinos do ADC1.

### Melhorias e Manutenção

Algumas sugestões para melhorias futuras incluem:

- Inclusão de novas configurações na classe de ajustes, como especificações técnicas variáveis da bateria.
- Aumento da robustez do sistema contra falhas de conectividade.
- Interface de usuário aprimorada no aplicativo móvel para facilitar a interação e o monitoramento.

Manter a documentação atualizada e criar testes para novas funcionalidades são essenciais para a manutenção contínua do projeto.

## Anexos e Referências

Imagens de diagramas e circuitos são incluídas para fornecer contexto visual e ajudar na montagem e compreensão do hardware. As referências fornecidas pelo professor e utilizadas durante o projeto estão disponíveis para consulta e aprofundamento dos conceitos aplicados.

## Contribuição e Licença

Contribuições são bem-vindas e devem seguir as diretrizes estabelecidas neste documento. O projeto está licenciado sob uma licença que permite o uso, distribuição e modificação, desde que os devidos créditos sejam mantidos e as alterações sejam documentadas.
