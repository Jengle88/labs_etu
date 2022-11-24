const express = require("express")
const router  = express.Router()
const fs = require("fs")

let database;
let localizeData = require("../utils/data_interceptor.js").localizeData

/**
 * @route GET /
 * @description Start page
 */
router.get("/", async (_, res) => {
    res.status(200)
    res.render("start")
})

/**
 * @route GET /admin_panel
 * @description Panel for administrator
 */
router.get("/admin_panel", async (req, res) => {
    database = JSON.parse(fs.readFileSync("./storage/database.json"))
    let usersInfo = database.users

    usersInfo.forEach(user => {
        localizeData(user)
    })

    res.status(200)
    res.render("admin_panel", {
        value: {
            usersInfo: usersInfo
        }
    })
})

/**
 * @route GET /profile/:user_id
 * @param userId User ID
 * @description Profile page of user
 */
router.get("/profile/:userId", async (req, res) => {
    database = JSON.parse(fs.readFileSync("./storage/database.json"))

    const userId = req.params.userId
    let user = null
    for(let _user of database.users) {
        if (_user.id === userId) {
            user = _user
            break
        }
    }
    if (user === null) {
        res.status(404)
        res.render("not_found")
        return
    }

    localizeData(user)

    let userPosts = database.posts.filter(post => post.userId === userId)
    let userFriends = user.friends.map(friendId => database.users.filter(user => user.id === friendId)[0])

    userFriends.forEach(friend => {
        localizeData(friend)
    })

    res.status(200)
    res.render("profile", {
        value: {
            user: user,
            userFriends: userFriends,
            userPosts: userPosts
        }
    })
})

//TODO ...

router.get("*", (_, res) => {
    res.status(404)
})

module.exports = router