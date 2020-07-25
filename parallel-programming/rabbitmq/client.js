'use strict'

const amqp = require('amqplib/callback_api')
const libxml = require('libxmljs')
const fs = require('fs')

const xml = fs.readFileSync('data/paper.xml', 'utf8')

amqp.connect('amqp://localhost', (err, conn) => {
    if (err) return console.error(err)

    conn.createChannel((err, channel) => {
        if (err) return console.error(err)
        const queue = 'xml'

        channel.assertQueue(queue, { durable: false })
        channel.sendToQueue(queue, Buffer.from(xml))

        console.log(`\x1b[42m[x] Sent \x1b[0m${xml}`)
    })

    setTimeout(() => {
        conn.close()
        process.exit(0)
    }, 500)
})
