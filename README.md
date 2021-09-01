# StonksLand

## Intro

StonksLand is a Qt desktop application used for displaying circulating currencies of the world. It shows you a map and a list of currencies. From these two you can either choose a currency you would like to explore or select a country whose currency you want to know. Either way, the program shows you the currencie's details as well as its real-time exchange rate to euros. You can also convert currencies (using real-time rates). 

Another feature of the app displays the currencie's rates to euros from the past several years. This is done through `QCharts` and another API. Left of the graph you can click on button `Display Live Markets` which will open a seperate window with some stock markets and a few important, market defining stocks such as AAPL, GOOG, MSFT and NOK. These are also made through `QCharts`.

## Specifications

### In-depth documentation

Please refer to the [wiki](https://gitlab-etu.ing.he-arc.ch/isc/2021-22/niveau-2/conception-logiciel-intro-donnees/g6/-/wikis/home).

### API

For this project we are using 2 seperate APIs. For the exchangerates we use [exchangerates.io](https://exchangeratesapi.io/documentation/). This API will send two seperate `jsons` on two seperate instances. One `json` contains the real-time exchange rates from nearly all the currencies to euros. The other gets a specific currencie's historical data for the rate-graph. The first `json` is requested on the apps startup and instantly saved to the `cache`. It is important to note that all `jsons` used whilst executing, are saved to the `cache`. This is to limit request numbers since we are too cheap to pay the subscriptions for the APIs. 

For the live market data we are using [marketstack.com](https://marketstack.com/documentation). This API gets a request everytime one tries to open the stock window. The reply contains quotes for the stocks from the past 100 days. We chose deliberatly to only show closing quotes since any other thing yould have been tedious to implement. Maybe in the future we can add candle charts or even some beautiful old school stock widget with a selection of stocks. It would not require other requests since we get volume, opening, percentage loss since 24h and so on in the reply. 

## Installation

There are two possibilities for installation:

* Windows installer (.exe) can be found [here](https://www.youtube.com/watch?v=dQw4w9WgXcQ)

* The code can be cloned and compiled using [Qt Creator](https://www.qt.io/download)

**DISCLAIMER:** This app will not work with Qt6! For the compilation with Qt, using Qt5 is paramount. This is due to the removal and deprecation of several tools used in this app in Qt6.

## Usage

![StonksLand](/uploads/716bc0f5865cf35f0dccd481c7cfb304/StonksLand.png)

The usage of this app is very straightforward. 

Two options for currency selection:
* Click on a currency in the provided list
* Click on a country in the provided map (zoom and ctrl-move horizontally are also available)

To convert money from one currency to another:
* Select currency of the amount to convert
* Select currency of the currency to convert into
* Type amount into given text field
* The converter will do the rest

To view live market data:
* Press big green button "Display live market data" really couldn't be any user-friendlier.

To view the graph of historical quotes to euros:
* Look at the bottom right of the window - the graph is There

## Licenses

* [marketstack.com](https://marketstack.com/terms)
* [exchangerates.io](https://exchangeratesapi.io/terms/)

This application and the usage of the APIs comply with the terms listed hereinabove. This application is not to be sold or used in a profitable way.

MIT License

Copyright (c) 2021 Coroli, Moreira and Abele

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.





