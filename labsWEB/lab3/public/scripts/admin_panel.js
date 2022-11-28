import {banUser} from "./client.js";

$(".ban_button").on("click", async function() {
    const userId = $(this).attr("id").split("ban_user#")[1]
    if (!isNaN(Number(userId))) {
        await banUser(userId)
    }
    location.reload()
})
