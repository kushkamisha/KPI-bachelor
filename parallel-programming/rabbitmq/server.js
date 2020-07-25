'use strict'

require('dotenv').config()
const amqp = require('amqplib/callback_api')
const libxml = require('libxmljs')
// const parser = require('xml2json')
const mongoose = require('mongoose')
const fs = require('fs')

const conn = mongoose.createConnection(`mongodb://${process.env.USERNAME}:\
${process.env.PASS}@ds263295.mlab.com:63295/parallel-lab9-delete`, {
    useNewUrlParser: true,
    useUnifiedTopology: true
})
const schema = new mongoose.Schema({
    title: { type: String },
    type: { type: String },
    frequency: { type: String },
    characteristics: [{
        colorful: { type: Boolean },
        volume: { type: Number },
        glossy: { type: Boolean },
        subscribtionIndex: { type: String }
    }]
})

const MyModel = conn.model('Hello', schema)

amqp.connect('amqp://localhost', (err, connection) => {
    if (err) return console.error(err)

    connection.createChannel((err, channel) => {
        if (err) return console.error(err)

        const queue = 'xml'

        channel.assertQueue(queue, { durable: false })

        console.log(`\x1b[42m [*] Waiting for messages in ${queue}. To exit press CTRL+C\x1b[0m`)

        channel.consume(queue, msg => {
            const data = msg.content.toString()
            console.log(`\x1b[42m [x] Received \x1b[0m${data}`)
            
            validate(data, (err, data) => {
                if (err) return console.error(err)
                console.log(`\x1b[42m [x] The xml is valid \x1b[0m`)
                saveToDb(data)
            })
        }, {
            noAck: true
        })
    })
})

function validate(data, callback) {
    const xsd = fs.readFileSync('data/paper.xsd', 'utf8')
    const xsdDoc = libxml.parseXml(xsd)
    const xmlDoc = libxml.parseXml(data)

    return xmlDoc.validate(xsdDoc) ?
        callback(null, xmlDoc.root().text()) :
        callback(xmlDoc.validationErrors)
}

async function saveToDb(xml) {
    const prettify = xml.split('\n  \n  \n').map(x => x.split('\n')
        .map(xx => xx.trim()).filter(xx => xx != ''))

    for (const paper of prettify) {
        const m = new MyModel

        m.title = paper[0]
        m.type = paper[1]
        m.frequency = paper[2]
        m.characteristics = {
            colorful: paper[3],
            volume: paper[4],
            glossy: paper[5],
            subscribtionIndex: paper[6]
        }

        await m.save()
        console.log(`\x1b[42m [x] Saved a paper to the db \x1b[0m`)
    }
}
