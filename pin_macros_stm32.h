/*-----------------------------------------------------------------------------
 *	pin_macros_stm32.h
 *-----------------------------------------------------------------------------
 *
 * Автор:  Слисенко Юрий
 *
 * Описание: Библиотека макросов для работы с портами микроконтроллеров
 *
 * STM32 (кроме семейства STM32F10x).
 *
 * Создана на основе библиотеки макросов для микроконтроллеров AVR 
 *
 * (файл pin_macros.h, автор Александр Редчук)
 *-----------------------------------------------------------------------------
 */


#ifndef PIN_MACROS_STM32_H
#define PIN_MACROS_STM32_H


/*
// Параметры, используеме в макросах для настройки вывода порта:
///////////////////////////////////////////////////////////////////////

OUT: Выход
IN: Вход
AF: Альтернативная функция порта
AN: Аналоговый вывод порта

PP: Выход push-pull
OD: Выход open-drain

PULLUP: Подтяжка вверх (pull-up)
PULLDOWN: Подтяжка вниз (pull-down)
NOPULL: Отключение подтяжки (pull-up/pull-down) для вывода порта

LS: Низкая скорость переключения (Low Speed)
MS: Средняя скорость переключения (Medium Speed)
HS: Высокая скорость переключения (High Speed)
*/


/*
Примеры:

// Описание вывода порта
//////////////////////////////////////////////////////////////////////////

#define	PIN1	A,10,L	// Порт GPIOA, разряд 10, активный уровень L (низкий)
#define	PIN2	B,2,H	// Порт GPIOB, разряд 2, активный уровень H (высокий)

// Настройка вывода порта
//////////////////////////////////////////////////////////////////////////

DRIVER(PIN1, OUT);		// Настройка PIN1 в качестве выхода

DRIVER(PIN2, IN);		// Настройка PIN2 в качестве входа

DRIVER(PIN1, AF);		// Настройка PIN1 в качестве альтернативной функции порта

DRIVER(PIN1, AN);		// Настройка PIN1 в качестве аналогового порта

DRIVER(PIN1, PP);		// Настройка PIN1 для работы в режиме push-pull

DRIVER(PIN1, OD);		// Настройка PIN1 для работы в режиме open-drain

DRIVER(PIN2, PULLUP);	// Включить подтяжку "вверх" (pull-up) на PIN2

DRIVER(PIN2, PULLDOWN);	// Включить подтяжку "вниз" (pull-down) на PIN2

DRIVER(PIN2, NOPULL);	// Отключение подтяжки на PIN2

DRIVER(PIN1, LS);		// Настроить низкую скорость переключения (Low Speed) вывода порта PIN1

DRIVER(PIN1, MS);		// Настроить среднюю скорость переключения (Medium Speed) вывода порта PIN1

DRIVER(PIN1, HS);		// Настроить высокую скорость переключения (High Speed) вывода порта PIN1


// Управление выводом порта
//////////////////////////////////////////////////////////////////////////

ON(PIN1);				// Установить активный уровень на выходе порта

OFF(PIN1);				// Установить пассивный (противоположный активному) уровень на
						// выходе порта

SET(PIN1);				// Установить высокий уровень на выходе порта

CLR(PIN1);				// Установить низкий уровень на выходе порта

CPL(Pin1);				// Инвертировать уровень на выходе порта

TOGGLE(Pin1);			// Инвертировать уровень на выходе порта

if (LATCH(PIN1)) {}		// Истинно, если на выходе порта установлен
						// активный уровень (в регистре ODR)

if (LATCH_H(PIN1)) {}	// Истинно, если на выходе порта установлен
						// высокий уровень (в регистре ODR)

if (LATCH_L(PIN1)) {}	// Истинно, если на выходе порта установлен
						// низкий уровень (в регистре ODR)


// Чтение входа порта
//////////////////////////////////////////////////////////////////////////

if (ACTIVE(PIN2)) {}	// Истинно, если на входе порта присутствует активный
						// уровень сигнала (в регистре IDR)

if (PIN_H(PIN2)) {}		// Истинно, если на входе порта присутствует высокий
						// уровень сигнала (в регистре IDR)

if (PIN_H(PIN2)) {}		// Истинно, если на входе порта присутствует высокий
						// уровень сигнала (в регистре IDR)

*/




#define	LH0		L
#define	LH1		L
#define	LH2		L
#define	LH3		L
#define	LH4		L
#define	LH5		L
#define	LH6		L
#define	LH7		L
#define	LH8		H
#define	LH9		H
#define	LH10	H
#define	LH11	H
#define	LH12	H
#define	LH13	H
#define	LH14	H
#define	LH15	H



#define _PM_BITNUM(port,bit,val)		(bit)
#define BITNUM(pin)						_PM_BITNUM(pin)
#define BITMASK(pin)					(1U << _PM_BITNUM(pin))

// IN (Input mode)
#define	_PM_IN(port,bit)			(GPIO##port->MODER &= ~GPIO_MODER_MODER##bit)

// OUT (General purpose output mode)
#define	_PM_OUT(port,bit)			(GPIO##port->MODER = (GPIO##port->MODER & ~GPIO_MODER_MODER##bit) | GPIO_MODER_MODER##bit##_0)

// AF (Alternate function mode)
#define	_PM_AF(port,bit)			(GPIO##port->MODER = (GPIO##port->MODER & ~GPIO_MODER_MODER##bit) | GPIO_MODER_MODER##bit##_1)

// ANALOG (Analog mode)
#define	_PM_ANALOG(port,bit)		(GPIO##port->MODER |= GPIO_MODER_MODER##bit)

// PP (Output push-pull)
#define	_PM_PP(port,bit)			(GPIO##port->OTYPER &= ~GPIO_OTYPER_OT_##bit)

// OD (Output open-drain)
#define	_PM_OD(port,bit)			(GPIO##port->OTYPER |= GPIO_OTYPER_OT_##bit)

// LS (Low speed)
#define	_PM_LS(port,bit)			(GPIO##port->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR##bit##_0)

// MS (Medium speed)
#define	_PM_MS(port,bit)			(GPIO##port->OSPEEDR = (GPIO##port->OSPEEDR & ~GPIO_OSPEEDR_OSPEEDR##bit) | GPIO_OSPEEDR_OSPEEDR##bit##_0)

// HS (High Speed)
#define	_PM_HS(port,bit)			(GPIO##port->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR##bit)

// NOPULL (pull-up/pull-down off)
#define	_PM_NOPULL(port,bit)		(GPIO##port->PUPDR &= ~GPIO_PUPDR_PUPDR##bit)

// PULLUP (pull-up on)
#define	_PM_PULLUP(port,bit)		(GPIO##port->PUPDR = (GPIO##port->PUPDR & ~GPIO_PUPDR_PUPDR##bit) | GPIO_PUPDR_PUPDR##bit##_0)

// PULLDOWN (pull-down on)
#define	_PM_PULLDOWN(port,bit)		(GPIO##port->PUPDR = (GPIO##port->PUPDR & ~GPIO_PUPDR_PUPDR##bit) | GPIO_PUPDR_PUPDR##bit##_1)




#define _PM_DRIVER(port,bit,val,mode)	_PM_##mode(port,bit)




///////////////////////////////////////////////////////////////////////////////
// mode: OUT, IN, AF, ANALOG, PP, OD, NOPULL, PULLUP, PULLDOWN, LS, MS, HS
#define DRIVER(pin,mode)				_PM_DRIVER(pin,mode)
///////////////////////////////////////////////////////////////////////////////




#define _PM_SETL(port,bit,dummy)		(GPIO##port->BRR = GPIO_BRR_BR_##bit)
#define _PM_SETH(port,bit,dummy)		(GPIO##port->BSRR = GPIO_BSRR_BS_##bit)
#define _PM_SET(port,bit,val)			_PM_SET##val(port,bit,dummy)
#define _PM_CLRL(port,bit,dummy)		_PM_SETH(port,bit,dummy)
#define _PM_CLRH(port,bit,dummy)		_PM_SETL(port,bit,dummy)
#define _PM_CLR(port,bit,val)			_PM_CLR##val(port,bit,dummy)
#define _PM_CPL(port,bit,val)\
do {\
	if (_PM_LATCH(port,bit,val)) _PM_CLR(port,bit,val); else _PM_SET(port,bit,val);\
} while (0)




///////////////////////////////////////////////////////////////////////////////
#define SET(pin)						_PM_SETH(pin)
#define CLR(pin)						_PM_SETL(pin)
#define ON(pin)							_PM_SET(pin)
#define OFF(pin)						_PM_CLR(pin)
#define CPL(pin)						_PM_CPL(pin)
#define TOGGLE(x)						_PM_CPL(pin)
///////////////////////////////////////////////////////////////////////////////




#define _PM_PINH(port,bit,dummy)		(GPIO##port->IDR & GPIO_IDR_##bit)
#define _PM_PINL(port,bit,dummy)		!_PM_PINH(port,bit,dummy)
#define _PM_PIN(port,bit,val)			_PM_PIN##val(port,bit,dummy)
#define _PM_LATCHH(port,bit,dummy)		(GPIO##port->ODR & GPIO_ODR_##bit)
#define _PM_LATCHL(port,bit,dummy)		!_PM_LATCHH(port,bit,dummy)
#define _PM_LATCH(port,bit,val)			_PM_LATCH##val(port,bit,dummy)




///////////////////////////////////////////////////////////////////////////////
#define ACTIVE(pin)						_PM_PIN(pin)
#define PIN_H(pin)						_PM_PINH(pin)
#define PIN_L(pin)						_PM_PINL(pin)
#define LATCH(pin)						_PM_LATCH(pin)
#define	LATCH_H(pin)					_PM_LATCHH(pin)
#define	LATCH_L(pin)					_PM_LATCHL(pin)
///////////////////////////////////////////////////////////////////////////////

#endif
