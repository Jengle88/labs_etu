const express = require('express');
const router = express.Router();



router.get("*", (_, res) => {
    res.status(404)
})

module.exports = router;
