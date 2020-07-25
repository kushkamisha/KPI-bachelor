'use strict'

const fs = require('fs')
const { exec } = require('child_process')
const http = require('http')
const Websocket = require('websocket').server

const index = fs.readFileSync('./index.html', 'utf8')

const server = http.createServer((req, res) => {
    res.writeHead(200)
    res.end(index)
})

server.listen(3000, () => {
    console.log('Listen port 8000')
})

const ws = new Websocket({
    httpServer: server,
    autoAcceptConnections: false
})

const clients = []

ws.on('request', req => {
    const connection = req.accept('', req.origin)
    clients.push(connection)
    console.log('Connected ' + connection.remoteAddress)
    
    connection.on('message', msg => {
        const dataName = `${msg.type}Data`
        const cmd = msg[dataName]
        console.dir(msg)
        console.log('Received: ' + cmd)
        if (!cmd) return

        exec(cmd, (error, stdout, stderr) => {
            if (error) {
                console.error(`exec error: ${error}`)
                return
            }

            console.log(`stdout: ${stdout}`)
            console.error(`stderr: ${stderr}`)

            const res = stdout ? stdout : stderr

            clients.forEach(client =>
                connection === client ? client.send(res) : null)
        })
    })
    
    connection.on('close', (reasonCode, description) => {
        console.log('Disconnected ' + connection.remoteAddress)
        console.dir({ reasonCode, description })
    })
})