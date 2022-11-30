const express = require('express');
const router = express.Router();
const fs = require("fs");

let database;

router.get("/get_user/:userId", async (req, res) => {
    database = JSON.parse(fs.readFileSync("./storage/database.json"))
    const userId = req.params.userId
    let userIndex = database.users.findIndex((user) => { return user.id === userId })
    if (userIndex === -1) {
        res.status(404)
        res.send("User not found :(")
    }

    res.status(200)
    res.send(database.users[userIndex])
})

router.put("/edit_user/:userId", async (req, res) => {
    database = JSON.parse(fs.readFileSync("./storage/database.json"))
    let editedUser = req.body.editedUser
    const userId = req.params.userId
    let userIndex = database.users.findIndex((user) => { return user.id === userId })
    if (userIndex === -1) {
        res.status(404)
        res.send("User not found :(")
    }

    let user = database.users[userIndex]
    if (user["id"] !== editedUser["id"]) {
        for (let post of database.posts) {
            if (post.userId === user.id)
                post.userId = editedUser["id"]
        }
        for (let tempUser of database.users) {
            for(let i = 0; i < tempUser.friends.length; i++) {
                if (tempUser.friends[i] === user.id)
                    tempUser.friends[i] = editedUser["id"]
            }
        }
    }


    for (let key in editedUser) {
        user[key] = editedUser[key]
    }

    let data = JSON.stringify(database)
    fs.writeFileSync("./storage/database.json", data)
    res.status(200)
    res.send(database.users)
})

router.put("/ban_user/:userId", async (req, res) => {
    database = JSON.parse(fs.readFileSync("./storage/database.json"))
    const userId = req.params.userId
    let userIndex = database.users.findIndex((user) => { return user.id === userId })
    if (userIndex === -1) {
        res.status(404)
        res.send("User not found :(")
    }

    let user = database.users[userIndex]
    user.status = "banned"

    let data = JSON.stringify(database)
    fs.writeFileSync("./storage/database.json", data)
    res.status(200)
    res.send(database.users)
})

router.delete("/delete_user/:userId", async (req, res) => {
    database = JSON.parse(fs.readFileSync("./storage/database.json"))
    const userId = req.params.userId
    let userIndex = database.users.findIndex((user) => { return user.id === userId })
    if (userIndex === -1) {
        res.status(404)
        res.send("User not found :(")
    }

    database.user.splice(userIndex, userIndex + 1)
    let data = JSON.stringify(database)
    fs.writeFileSync("./storage/database.json", data)
    res.status(200)
    res.send(database.users)
})

router.get("*", (_, res) => {
    res.status(404)
})

module.exports = router;
