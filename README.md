# Auto-Ração: Alimentação automática
Projeto para automatizar a alimentação do Pet como trabalho da disciplina de Objetos Inteligentes Conectados

## Protótipo
A fim de automatizar um processo do dia a dia das pessoas que possuem Pet em casa, pensamos num mecanismo para Alimentação automática, onde pode-se liberar a comida do Pet pelo aplicativo MQTT Dash ou ao detectar a presença do Pet perto do mecanismo. A quantidade de ração desce aos poucos para que não haja desperdício, utilizamos também metade da garrafa pet para funilar a descida através do cano.

## Mecanismo
O protótipo foi feito com materiais de fácil acesso como partes da caixa de papelão e um cano, também utilizamos os seguintes componentes eletrônicos: 
* Arduino UNO
* Sensor PIR (presença e movimento)
* Motor de engrenagem
* Bateria 6V
* Módulo de ethernet ENC28J60
* Caixa de papelão recortada em retângulo 60cm de altura e 30cm de largura
* Palito para segurar a porta que fica no cano
* A porta foi feita de papelão, cortada em formato circular, um pouco menor que a largura do cano para que seja possível girar

## Desenvolvimento
O Software foi implementado na linguagem C, utilizando a IDE do Arduíno. O circuito foi feito utilizando a ferramenta Fritzing.
Como protocolo de comunicação utilizamos o MQTT (protocolo de comunicação máquina para máquina) e em conjunto o aplicativo MQTT Dash para controlar os mecanismos de liberar ração e acompanhar a presença do Pet pela interface.

## Circuito
Para reproduzir este protótipo, deve-se seguir o circuito abaixo com os respectivos componentes já citados anteriormente.

![circuito-p](https://user-images.githubusercontent.com/14910223/85233504-4da49f00-b3dd-11ea-943c-20c928cc9f44.jpg)

Circuito do motor de engrenagem, que fica a encaixado no Arduíno:

![85233521-6ad96d80-b3dd-11ea-88f9-c8bc3ea3d51e](https://user-images.githubusercontent.com/14910223/85241101-059f6f80-b411-11ea-9ce4-1d2ceb3774ec.png)
