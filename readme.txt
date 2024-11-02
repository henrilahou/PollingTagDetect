IoT Systems Advanced - Project 1: NFC

Dit project betreft de ontwikkeling van een NFC-systeem met behulp van twee microcontrollers, waarbij NFC-tags worden uitgelezen en verwerkt via seriële communicatie.

Overzicht

Het systeem bestaat uit twee microcontrollerborden die via een seriële verbinding (USART) communiceren. Het STM32F411RE-bord, uitgerust met een X-CUBE-NFC5 NFC-module, leest NFC-ID’s uit en stuurt deze door naar het STM32F746G Discovery-bord. Op dit tweede bord worden de ID’s verder verwerkt en vergeleken met een vooraf gedefinieerde lijst van geldige ID’s.

Functionaliteit

	•	NFC-Uitlezing: Het STM32F411RE-bord met de X-CUBE-NFC5 module leest NFC-tags uit.
	•	Communicatie via USART: De uitgelezen NFC-ID’s worden via een seriële verbinding doorgestuurd naar het STM32F746G-bord.
	•	Verwerking en Actie: Het STM32F746G-bord:
	•	Slaat de ontvangen ID’s op in een message queue voor verdere verwerking.
	•	Vergelijkt elk ontvangen ID met een lijst van geldige, vooraf ingestelde ID’s.
	•	Als een ID overeenkomt:
	•	Licht het MultiEdit-veld op het scherm gedurende 3 seconden groen op om een geldige scan aan te geven.
	•	Gaat de LED op het STM32F746G-bord gedurende 3 seconden aan.
	•	Activeert een uitgang voor een magnetisch deurslot, waardoor het slot gedurende 3 seconden geopend blijft.

Code Structuur

De code voor dit project is opgesplitst over twee verschillende repositories, elk specifiek voor een van de microcontrollers.

	1.	STM32F411RE-bord:
	•	Dit programma beheert de NFC-lezer en zorgt ervoor dat NFC-ID’s worden uitgelezen en via USART worden verstuurd naar het STM32F746G-bord.
	•	Repository link: https://github.com/henrilahou/PollingTagDetect
	2.	STM32F746G-bord:
	•	Dit programma ontvangt de NFC-ID’s, slaat ze op in een message queue, vergelijkt ze met de geldige ID-lijst en voert de acties uit als een ID geldig blijkt.
	•	Repository link: https://github.com/henrilahou/PollingTagDetect/tree/STM32F7

Aansluitingen en Pin Configuratie

Om de seriële communicatie tussen de twee borden op te zetten en de voeding correct te verbinden, volgen hier de nodige aansluitingen:

Seriële Verbinding (USART)

	•	Verbind de RX-pin van het STM32F411RE-bord (op connector 3) met D0 (RX), de eerste pin op connector 4 van het STM32F746G Discovery-bord. Dit zorgt voor de dataoverdracht van het NFC-bord naar het display-bord.

Voeding van het STM32F411RE-bord

Voor de voeding van het STM32F411RE-bord zijn er twee mogelijkheden:

	1.	Via het STM32F746G-bord:
	•	Verbind de GND-pin van het STM32F411RE met de GND van het STM32F746G.
	•	Verbind de VIN-pin van het STM32F411RE met de 5V-pin van het STM32F746G.
	2.	Via een aparte voeding:
	•	Sluit het STM32F411RE-bord direct aan op een mini-USB B-kabel om het bord apart van stroom te voorzien.

Deze configuratie zorgt ervoor dat beide borden effectief samenwerken om NFC-tags te lezen en de juiste acties uit te voeren op basis van de ontvangen NFC-ID’s.
