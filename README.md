# STM32F103 Minimalist Template

Минималистичный стартовый шаблон для разработки под плату **STM32F103 BluePill**

Цель проекта - создание базы для быстрой разработки простых приложений под плату BluePill

## Ключевые особенности

- Чистый **CMSIS**
- Собственный минимальный скрипт линковки
- Минимальный тулчейн-файл для **CMake**
- Прошивка через **OpenOCD**

## Устройства

1. Программатор ST-Link или его китайская копия

2. Сама плата BluePill, очевидно

## Зависимости 

1. [ARM GNU Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
   
2. [CMake](https://cmake.org/download/) + [Ninja](https://github.com/ninja-build/ninja)
   
3. [OpenOCD](https://openocd.org/pages/getting-openocd.html)

4. [Visual Studio Code](https://code.visualstudio.com/download) по желанию)

## Как начать разработку?

1. Установить все необходимые зависимости
  
2. **Убедиться, что пути к CMake, arm-none-eabi-gcc и ninja находятся в PATH**
  
3. Открыть шаблон в любой среде разработки и начать творить 

## Как собрать проект?

1. С помощью комбинации клавиш **Ctrl+Shift+B** в VSCode
   
2. Нет VSCode? Соберите через терминал:

   2.1 `cmake -preset Cortex-M3`
   
   2.2 `cmake --build --preset Cortex-M3`

>Результат - генерация директории build, а в ней - файлов прошивки Flash.elf и Flash.bin

## Как прошить STM32?

1. Подключите ST-Link к STM32 и ПК
  
2. Загрузите прошивку через терминал:

   2.1 `openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c 'program (путь к прошивке)/Flash.bin 0x08000000 verify reset exit'`

>Результат - прошивка загружена в ваш контроллер! Если вы ничего не меняли в main.c, то на вашей плате заморгает один из светодиодов


