<h1 align="center">Welcome to ioct 👋</h1>
<p>
  <a href="https://www.npmjs.com/package/iot" target="_blank">
    <img alt="Version" src="https://img.shields.io/npm/v/iot.svg">
  </a>
  <a href="https://github.com/prichardsondev/ioct#readme" target="_blank">
    <img alt="Documentation" src="https://img.shields.io/badge/documentation-yes-brightgreen.svg" />
  </a>
  <a href="https://github.com/prichardsondev/ioct/graphs/commit-activity" target="_blank">
    <img alt="Maintenance" src="https://img.shields.io/badge/Maintained%3F-yes-green.svg" />
  </a>
  <a href="https://github.com/prichardsondev/ioct/blob/master/LICENSE" target="_blank">
    <img alt="License: ISC" src="https://img.shields.io/github/license/prichardsondev/iot" />
  </a>
</p>

> Raspberry <-> Arduino Communication with Xbee radios. App structure: expressjs.com & socket.io

> express.com - serve html page with single button to toggle pin on arduino

> socket.io - messages between server (app.js) and client (index.html). Keeps all versions of client insync with state of backend (in memory js object). Is the pin on the arduino high or low (relay/reed open or closed).

> serialport.io & npm xbee-api  - listen for state of remote xbee radios - fires socket.io.emit to inform clients. Also sends state change from client (button click) to remote xbee radios to toggle arduino pins

> nginx.com can be used as a reverse proxy listening on 80 and forwarding to port your app is running on (3000 in this example)

> dataplicity.io or balena.io can be use to expose port 80 to the world - I use/like both. dataplicity is quicker to get up and running

>

>

### 🏠 [Homepage](https://github.com/prichardsondev/ioct#readme)

## Install

```sh
Note: this was designed to run on Raspberry PI but could work anywhere you have node installed

cd pi
npm install
```
## Run

```sh
npm start
```

## Run tests

```sh
npm run test
```

## Author

👤 **prichardsondev**

* Github: [@prichardsondev](https://github.com/prichardsondev)

## 🤝 Contributing

Contributions, issues and feature requests are welcome!<br />Feel free to check [issues page](https://github.com/prichardsondev/ioct/issues). You can also take a look at the [contributing guide](https://github.com/prichardsondev/ioct/blob/master/CONTRIBUTING.md).

## Show your support

Give a ⭐️ if this project helped you!

## 📝 License

Copyright © 2020 [prichardsondev](https://github.com/prichardsondev).<br />
This project is [ISC](https://github.com/prichardsondev/ioct/blob/master/LICENSE) licensed.

***
_This README was generated with ❤️ by [readme-md-generator](https://github.com/kefranabg/readme-md-generator)_