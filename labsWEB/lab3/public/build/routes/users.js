const express = require('express');
const router = express.Router();
const fs = require("fs");
const {localizeData} = require("../utils/data_interceptor.js");

let database;

router.get("/get_users", async (req, res) => {
    database = JSON.parse(fs.readFileSync("./storage/database.json"))
    let users = database.users
    users.forEach(user => { localizeData(user) })

    res.status(200)
    res.send(users)
})

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

router.get("/get_user_with_localize/:userId", async (req, res) => {
    database = JSON.parse(fs.readFileSync("./storage/database.json"))
    const userId = req.params.userId
    let userIndex = database.users.findIndex((user) => { return user.id === userId })
    if (userIndex === -1) {
        res.status(404)
        res.send("User not found :(")
    }
    let user = database.users[userIndex]
    let localizeUser = Object.assign({}, user)
    localizeUser = localizeData(localizeUser)
    let userInfo = {
        user: user,
        localizeUser: localizeUser
    }
    res.status(200)
    res.send(userInfo)
})

router.get("/get_full_user_info/:userId", async (req, res) => {
    database = JSON.parse(fs.readFileSync("./storage/database.json"))
    const userId = req.params.userId
    let userIndex = database.users.findIndex((user) => { return user.id === userId })
    if (userIndex === -1) {
        res.status(404)
        res.send("User not found :(")
    }
    let user = database.users[userIndex]
    user = localizeData(user)
    let friendsPosts = database.posts.filter(post => user.friends.includes(post.userId))
    let userPosts = database.posts.filter(post => post.userId === userId)
    let userFriends = user.friends.map(friendId => database.users.filter(user => user.id === friendId)[0])

    userFriends.forEach(friend => {
        localizeData(friend)
    })

    let fullUserInfo = {
        user: user,
        userFriends: userFriends,
        userPosts: userPosts,
        friendsPosts: friendsPosts
    }

    res.status(200)
    res.send(fullUserInfo)
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
