import {banUser, deletePost} from "./client.js";

$(".ban_button").on("click", async function() {
    const userId = $(this).attr("id").split("ban_user#")[1]
    if (!isNaN(Number(userId))) {
        await banUser(userId)
    }
    location.reload()
})

$(".delete_post").on("click", async function() {
    const postId = $(this).attr("id").split("deletePost#")[1]
    await deletePost(postId)
    location.reload()
})

$("#profile_wall_header_friends_posts").on("click", function () {
    $(this).attr("class", "profile-wall-header-active")
    $("#profile_wall_header_posts").attr("class", "profile-wall-header-inactive")
    $("#profile_wall_header_friends").attr("class", "profile-wall-header-inactive")

    $("#profile_wall_posts").attr("class", "active")
    $("#profile_wall_friends").attr("class", "inactive")

    $("#profile_wall_friends_posts_column").css("display", "flex")
    $("#profile_wall_posts_column").css("display", "none")
})

$("#profile_wall_header_posts").on("click", function () {
    $(this).attr("class", "profile-wall-header-active")
    $("#profile_wall_header_friends_posts").attr("class", "profile-wall-header-inactive")
    $("#profile_wall_header_friends").attr("class", "profile-wall-header-inactive")

    $("#profile_wall_posts").attr("class", "active")
    $("#profile_wall_friends").attr("class", "inactive")

    $("#profile_wall_friends_posts_column").css("display", "none")
    $("#profile_wall_posts_column").css("display", "flex")
})

$("#profile_wall_header_friends").on("click", function () {
    $(this).attr("class", "profile-wall-header-active")
    $("#profile_wall_header_friends_posts").attr("class", "profile-wall-header-inactive")
    $("#profile_wall_header_posts").attr("class", "profile-wall-header-inactive")

    $("#profile_wall_posts").attr("class", "inactive")
    $("#profile_wall_friends").attr("class", "active")
})
