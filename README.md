# Макросы для настройки и управления выводами портов микроконтроллеров STM32.


## Введение
-------------------------------------------------------------------------------

Макросы предназначены для разработки более компактных и удобочитаемых исходных
текстов программ, в которых используются порты ввода-вывода (GPIO)
микроконтроллеров семейства STM32 (кроме STM32F10x). При этом размер
результирующего кода программы и скорость выполнения операций ввода-вывода при
использовании макросов остаются такими же, как и в случае непосредственного
использования регистров GPIO. Более того, удобство использования макросов
заключается в отсутствии необходимости поиска в документации информации о
назначении разрядов регистров управления GPIO, наглядности, экономии времени
при написании и сопровождении исходных текстов программ, а также уменьшению
потенциальных ошибок.

Например, если необходимо настроить вывод порта PA10 в качестве выхода
open-drain (с открытым стоком) с низкой скоростью переключения, а затем
установить этот вывод в состояние логического нуля, то фрагмент исходного кода
с использованием макросов будет выглядеть следующим образом:

```
#define	PIN1	A,10,L	// Объявление вывода порта, где:
			// PIN1 - произвольное название вывода порта,
			// A - Вывод порта принадлежит GPIOA,
			// 10 - Номер разряда порта,
			// L - Активный уровень "низкий".

DRIVER(PIN1, OD);// Настройка вывода порта на режим работы open-drain, где:
			// PIN1 - Предварительно объявленный вывод порта,
			// OD - Режим open-drain,

DRIVER(PIN1, LS);// Настройка скорости переключения вывода порта, где:
			// PIN1 - Предварительно объявленный вывод порта,
			// LS - Низкая скорость переключения (Low Speed).

DRIVER(PIN1, OUT);// Настройка вывода порта в качестве выхода, где:
			// PIN1 - Предварительно объявленный вывод порта,
			// OUT - Режим выхода,

ON(PIN1);	// Установка активного уровня (L) на выводе порта PIN1.
```

После обработки препроцессором эти макросы развернутся к следующему виду:

```
//DRIVER(PIN1, OD);
GPIOA->OTYPER |= GPIO_OTYPER_OT_10;

//DRIVER(PIN1, LS);
GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR10_0;

//DRIVER(PIN1, OUT);
GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODER10) | GPIO_MODER_MODER10_0;

//ON(PIN1);
GPIOA->BSRR = GPIO_BSRR_BR_10;
```

Очевидно, что исходный код, реализованный с помощью макросов дает лучшее
понимание работы программы.


## Использование
-------------------------------------------------------------------------------

Для использования макросов необходимо скопировать файл pin_macros_stm32.h
в папку с проектом, а в файле с исходным кодом разместить следующие строки:

_Пример_:

```
#include "stm32f0xx.h"	// Этот файл включается для проектов на базе
						// микроконтроллеров семейства STM32F0xx. 
						// Для других семейств нужно подключать файл,
						// соответствующий данному семейству
						
#include "pin_macros_stm32.h"
```

_ПРИМЕЧАНИЕ:_ 

Макросы с префиксом _PM являются служебными и не предназначены для
непосредственного использования в исходном тексте.


## Описание
-------------------------------------------------------------------------------


### Объявление вывода порта

Выводы портов, управление которыми в программе будет производится с помощью
макросов необходимо объявить следующим образом:

```
#define	ИМЯ	 ПОРТ,РАЗРЯД,АКТИВНОСТЬ
```

Где:

ИМЯ - Произвольное название вывода порта; 

ПОРТ - Символ порта (символ 'A' для порта GPIOA, 'B' для порта GPIOB и т.д.);

РАЗРЯД - Номер разряда порта GPIOx (Число от 0 до 15);

АКТИВНОСТЬ - Символ, указывающий на активное состояние вывода порта
		(символ 'L' - низкий уровень, 'H' - высокий уровень);

_Примеры:_

```
#define	PIN1	A,10,L	// Порт GPIOA, разряд 10, активный уровень L (низкий)
#define	PIN2	B,2,H	// Порт GPIOB, разряд 2, активный уровень H (высокий)
```


### Настройка вывода порта

Настройка вывода порта на нужный режим работы производится с помощью
макроса DRIVER(...) следующим образом:

```
DRIVER(ИМЯ, РЕЖИМ);
```

Где:

ИМЯ - Предварительно объявленный вывод порта;

РЕЖИМ - Режим работы вывода порта. Возможно одно из следующих значений:

- OUT: Выход (push-pull или open-drain);
- IN: Вход цифровой (без подтяжки или с подтяжкой pull-up/pull-down);
- AF: Альтернативная функция порта;
- ANALOG: Аналоговый порт;
- PP: Выход Push-Pull
- OD: Выход Open-Drain
- LS: Низкая скорость переключения (Low Speed).
- MS: Средняя скорость переключения (Medium Speed);
- HS: Высокая скорость переключения (High Speed);
- PULLUP: Подтяжка вверх (pull-up);
- PULLDOWN: Подтяжка вниз (pull-down);
- NOPULL: Без подтяжки (input floating);

_ПРИМЕЧАНИЕ:_

Параметры LS, MS, HS используются в случае, если вывод порта работает как выход.

_Примеры_:

```
DRIVER(PIN1, OUT);		// Настройка PIN1 в качестве выхода

DRIVER(PIN2, IN);		// Настройка PIN2 в качестве цифрового входа

DRIVER(PIN1, AF);		// Настройка PIN1 для альтернативной функции

DRIVER(PIN2, ANALOG);	// Настройка PIN2 в качестве аналогового порта

DRIVER(PIN1, PP);		// Настройка PIN1 в качестве выхода push-pull

DRIVER(PIN1, OD);		// Настройка PIN1 в качестве выхода open-drain

DRIVER(PIN1, LS);		// Установить низкую скорость переключения
						// (Low Speed) для PIN1

DRIVER(PIN1, MS);		// Установить среднюю скорость переключения
						// (Medium Speed) для PIN1

DRIVER(PIN1, HS);		// Установить высокую скорость переключения
						// (High Speed) для PIN1

DRIVER(PIN2, NOPULL);	// Отключить подтяжку на PIN2

DRIVER(PIN2, PULLUP);	// Включить подтяжку "вверх" (pull-up) на PIN2

DRIVER(PIN2, PULLDOWN);	// Включить подтяжку "вниз" (pull-down) на PIN2
```


### Управление выходами порта

Управление выводом порта, который настроен в качестве выхода в режиме OUT
осуществляется с помощью следующих макросов:

```
ON(ИМЯ);		// Установить активный уровень на выходе порта.
OFF(ИМЯ);		// Установить пассивный уровень (противоположный активному)
				// на выходе порта.
SET(ИМЯ);		// Установить высокий уровень на выходе порта.
CLR(ИМЯ);		// Установить низкий уровень на выходе порта.
CPL(ИМЯ); 		// Инвертировать уровень на выходе порта.
TOGGLE(ИМЯ);	// См. CPL(ИМЯ)

if (LATCH(ИМЯ)) {}		// Проверка активного уровня на выходе порта.
if (LATCH_H(ИМЯ)) {}	// Проверка высокого уровня на выходе порта.
if (LATCH_L(ИМЯ)} {}	// Проверка низкого уровня на выходе порта.
```

Где:

ИМЯ - Предварительно объявленный вывод порта;

_ПРИМЕЧАНИЕ:_
Макросы CPL() и TOGGLE() являются синонимами. 

Макрос ON(ИМЯ) осуществляет установку активного уровня на выходе порта, т.е.
если при объявлении вывода порта был указан высокий активный уровень при помощи
символа 'H', то макрос ON(ИМЯ) развернется препроцессором в команду записи
единицы в соответствующий разряд регистра GPIOx_BSRR, обеспечив тем самым
высокий уровень на выходе порта. Если же при объявлении вывода порта указан
низкий уровень (при помощи символа 'L'), то макрос ON(ИМЯ) развернется в
команду записи единицы в соответствующий разряд регистра GPIOx_BRR, в
результате чего на выходе порта установится низкий уровень.

Макрос OFF(ИМЯ) осуществляет установку уровня на выходе порта, противоположного
активному, т.е. если при объявлении вывода порта был указан высокий активный
уровень при помощи символа 'H', то макрос OFF(ИМЯ) развернется препроцессором в
команду записи единицы в соответствующий разряд регистра GPIOx_BRR, обеспечив
тем самым низкий уровень на выходе порта. Если же при объявлении вывода порта
указан низкий уровень при помощи символа 'L', то макрос OFF(ИМЯ) развернется
в команду записи единицы в соответствующий разряд регистра GPIOx_BSRR, в
результате чего на выходе порта установится высокий уровень.

Макросы SET(ИМЯ) и CLR(ИМЯ) используются для установки на выходе порта
соответственно высокого и низкого уровня независимо от того, какой уровень был
указан в качестве активного (символ 'L' или 'H') при объявлении вывода порта.
Макрос SET(ИМЯ) реализуется посредством записи единицы в соответствующий
разряд регистра GPIOx_BSRR, а макрос CLR(ИМЯ) посредством записи единицы в
соответствующий разряд регистра GPIOx_BRR.

Макрос CPL(ИМЯ) (или TOGGLE(ИМЯ)) производит инверсию уровня на выходе порта.
Для определения текущего состояния выхода порта производится чтение выходного
регистра GPIOx_ODR, и, в зависимости от состояния разряда, номер которого был
указан при объявлении вывода порта осуществляется установка инверсного значения
посредством записи единицы в соответствующий разряд регистра GPIOx_BSRR или
GPIOx_BRR.

_Примеры_:

```
#define	PIN1	A,10,L	// Порт GPIOA, разряд 10, активный уровень L (низкий)

DRIVER(PIN1, PP);	// Установка режима push-pull для PIN1
DRIVER(PIN1, HS);	// Настройка PIN1 для работы
					// с высокой скоростью переключения (High Speed)
DRIVER(PIN1, OUT);	// Настройка PIN1 для работы в качестве выхода
ON(PIN1);			// Установка активного уровня на выходе порта PA10 
					//(в данном случае - низкого)
OFF(PIN1);			// Установка пассивного уровня на выходе порта PA10 
					//(в данном случае - высокого)
SET(PIN1);			// Установка высокого уровня на выходе порта PA10 
CLR(PIN1);			// Установка низкого уровня на выходе порта PA10 
CPL(PIN1);			// Инверсия уровня на выходе порта PA10
```


Макрос LATCH(ИМЯ) возвращает ненулевое значение, если выход порта установлен в
активное состояние, т.е. если соответствующий разряд регистра GPIOx_ODR
установлен в состояние, соответствующее активному уровню вывода порта при его
объявлении.

Макрос LATCH_H(ИМЯ) возвращает ненулевое значение, если выход порта установлен
в состояние высокого уровня, т.е. если в соответствующем разряде регистра
GPIOx_ODR установлена логическая единица.

Макрос LATCH_L(ИМЯ) возвращает ненулевое значение, если выход порта установлен
в состояние низкого уровня, т.е. если в соответствующем разряде регистра
GPIOx_ODR установлен логический ноль.

_Примеры_:

```
#define	PIN1	A,10,L	// Порт GPIOA, разряд 10, активный уровень L (низкий)

DRIVER(PIN1, OD);	// Установка режима open-drain для PIN1
DRIVER(PIN1, LS);	// Настройка PIN1 для работы
					// с низкой скоростью переключения (Low Speed)
DRIVER(PIN1, OUT);	// Настройка PIN1 для работы в качестве выхода

...

if (LATCH(PIN1))
{
	// Здесь код выполнится, если в разряде 10 выходного регистра GPIOA_ODR
	// установлен активный уровень (в данном случае - низкий)
	...
}

if (LATCH_H(PIN1))
{
	// Здесь код выполнится, если в разряде 10 выходного регистра GPIOA_ODR
	// установлена логическая единица
	...
}

if (LATCH_L(PIN1))
{
	// Здесь код выполнится, если в разряде 10 выходного регистра GPIOA_ODR
	// установлен логический ноль.
	...
}
```


### Чтение входов порта

Использование вывода порта, который настроен в качестве цифрового входа
(режим IN) осуществляется при помощи следующих макросов:

```
ACTIVE(ИМЯ);
PIN_H(ИМЯ);
PIN_L(ИМЯ);
```

Где:

ИМЯ - Предварительно объявленный вывод порта;

Макрос ACTIVE(ИМЯ) возвращает ненулевое значение, если на входе порта
присутствует уровень сигнала, соответствующий активному уровню вывода порта при
его объявлении, т.е. если требуемый разряд регистра GPIOx_IDR установлен в
состояние, соответствующее активному уровню вывода порта при его объявлении.

Макрос PIN_H(ИМЯ) возвращает ненулевое значение, если на входе порта
присутствует высокий уровень сигнала, т.е. если в требуемом разряде регистра
GPIOx_IDR установлена логическая единица.

Макрос PIN_L(ИМЯ) возвращает ненулевое значение, если на входе порта
присутствует низкий уровень сигнала, т.е. если в требуемом разряде регистра
GPIOx_IDR установлен логический ноль.

_Примеры_:

```
#define	PIN2	B,2,L	// Порт GPIOB, разряд 2, активный уровень L (низкий)

DRIVER(PIN2, NOPULL);	// Отключение подтяжки на PIN2
DRIVER(PIN2, IN);		// Настройка PIN2 для работы в качестве цифрового входа

...

if (ACTIVE(PIN2))
{
	// Здесь код выполнится, если на входе порта PB2 присутствует активный
	// уровень сигнала (в данном случае - низкий)
	...
}

if (PIN_H(PIN2))
{
	// Здесь код выполнится, если на входе порта PB2 присутствует высокий
	// уровень сигнала
	...
}

if (PIN_L(PIN2))
{
	// Здесь код выполнится, если на входе порта PB2 присутствует низкий
	// уровень сигнала
	...
}
```
