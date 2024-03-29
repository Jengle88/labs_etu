const express = require("express")
const router  = express.Router()
const fs = require("fs")
const path = require("path");

let database;

/**
 * @route GET /
 * @description Start page
 */
router.get("/", async (_, res) => {
    res.status(200)
    res.sendFile(path.join(__dirname, "../public/views/start.html"))
})

/**
 * @route GET /admin_panel
 * @description Panel for administrator
 */
router.get("/admin_panel", async (req, res) => {
    database = JSON.parse(fs.readFileSync("./storage/database.json"))
    // let usersInfo = database.users
    // usersInfo.forEach(user => {
    //     localizeData(user)
    // })

    res.status(200)
    res.sendFile(path.join(__dirname, "../public/views/admin_panel.html"))
})

/**
 * @route GET /profile/:userId
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
        return
    }
    //
    // localizeData(user)
    //
    // let friendsPosts = database.posts.filter(post => user.friends.includes(post.userId))
    // let userPosts = database.posts.filter(post => post.userId === userId)
    // let userFriends = user.friends.map(friendId => database.users.filter(user => user.id === friendId)[0])
    //
    // userFriends.forEach(friend => {
    //     localizeData(friend)
    // })

    res.status(200)
    res.sendFile(path.join(__dirname, "../public/views/profile.html"))
})

router.get("/edit_profile/:userId", async (req, res) => {
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
        return
    }

    res.status(200)
    res.sendFile(path.join(__dirname, "../public/views/edit_profile.html"))
})

router.get("*", (_, res) => {
    res.status(404)
})

module.exports = router