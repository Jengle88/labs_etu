const express = require('express');
const router = express.Router();
const fs = require('fs');

let database;

/**
 * @route DELETE api/posts/delete_post/:postId
 * @param postId Post ID
 * @description Delete post from database
 */
router.delete("/delete_post/:postId", async (req, res) => {
    database = JSON.parse(fs.readFileSync("./storage/database.json"))

    const postId = req.params.postId
    let postIndex = database.posts.findIndex((post) => { return post.id === postId })
    if (postIndex === -1) {
        res.status(404)
        res.send("Post not found")
    }

    database.posts.splice(postIndex, postIndex + 1)
    let data = JSON.stringify(database)
    fs.writeFileSync("./storage/database.json", data)
    res.status(200)
    res.send(database.posts)
})

router.get("*", (_, res) => {
    res.status(404)
})

module.exports = router;
