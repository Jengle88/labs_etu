import {banUser, getFullUserInfo} from "./client.js";
import {deletePost} from "../../scripts/client.js";

$(document)
    .ready(async function () {
        // Receive user data
        const userId = document.location.href.split("/").slice(-1)
        const fullUserInfo = await getFullUserInfo(userId)
        const user = fullUserInfo.user
        const userFriends = fullUserInfo.userFriends
        const userPosts = fullUserInfo.userPosts
        const friendsPosts = fullUserInfo.friendsPosts

        // Fill page data
        $("#profile_user_image").attr("src", user.image_link)
        $("#profile_id").text(user.id)
        $("#profile_name").text(user.name)
        $("#profile_birth").text(user.birth)
        $("#profile_gender").text(user.gender)
        $("#profile_role").text(user.role)
        $("#profile_status").text(user.status)
        $("#profile_email").text(user.email)

        $(".ban_button").attr("id", `ban_user#${user.id}`)

        friendsPosts.forEach(post => {
            let postInfo = `
                        <div id="profile_wall_post_text">
                            <div id="profile_wall_post_text_header">
                                <div id="profile_wall_post_text_header_user_info"><a class="profile-wall-post-text-username" href="/profile/${post.userId}">${userFriends.find((user) => {
                return user.id === post.userId
            }).name}</a>
                                    <p>${post.date}</p></div>
                                <img class="action-button delete_post" type="button" src="../drawable/ic_delete.png" id="deletePost#${post.id}">
                            </div>
                            <p id="profile_wall_post_text_value">${post.text}</p></div>                    
                    `
            $("#profile_wall_friends_posts_column").append($(postInfo))
        })
        userPosts.forEach(post => {
            let postInfo = `
                        <div id="profile_wall_post_text">
                            <div id="profile_wall_post_text_header">
                                <div id="profile_wall_post_text_header_user_info"><a class="profile-wall-post-text-username" href="/profile/${post.userId}">${user.name}</a>
                                    <p>${post.date}</p></div>
                                <img class="action-button delete_post" type="button" src="../drawable/ic_delete.png" id="deletePost#${post.id}">
                            </div>
                            <p id="profile_wall_post_text_value">${post.text}</p></div>                    
                    `
            $("#profile_wall_posts_column").append($(postInfo))
        })
        userFriends.forEach(friend => {
            let friendInfo = `
                        <tr>
                            <th class="profile_table_user_name" scope="row">${friend.name}</th>
                            <td class="profile_table_birth_date" scope="">${friend.birth}</td>
                            <td class="profile_table_gender" scope="">${friend.gender}</td>
                            <td class="profile_table_role" scope="">${friend.role}</td>
                            <td class="profile_table_status" scope="">${friend.status}</td>
                            <td class="profile_table_email" scope="">${friend.email}</td>
                            <td class="profile_table_buttons" scope=""><a href="/profile/${friend.id}">
                                <button class="button-primary action-button" type="button">Профиль</button>
                            </a>
                                <button class="button-danger action-button ban_button" type="button" id="ban_user#${friend.id}">Заблокировать</button>
                            </td>
                        </tr>
                    `
            $("#table_body").append($(friendInfo))
        })


        // Set user info for buttons
        $(".profile_edit_user_link").attr("href", `/edit_profile/${user.id}`)

        $(".ban_button")
            .on("click", async function () {
                const userId = $(this).attr("id").split("ban_user#")[1]
                if (!isNaN(Number(userId))) {
                    await banUser(userId)
                }
                location.reload()
            })

        $(".delete_post").on("click", async function () {
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
    })
