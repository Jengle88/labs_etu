import {banUser} from "./client.js";

$(".ban_button").on("click", async function() {
    const userId = $(this).attr("id").split("banUser#")[1]
    if (!isNaN(Number(userId))) {
        await banUser(userId)
    }
    location.reload()
})

$("#profile_wall_header_posts").on("click", function () {
    $(this).attr("class", "profile-wall-header-active")
    $("#profile_wall_header_friends").attr("class", "profile-wall-header-inactive")
})

$("#profile_wall_header_friends").on("click", function () {
    $(this).attr("class", "profile-wall-header-active")
    $("#profile_wall_header_posts").attr("class", "profile-wall-header-inactive")
})