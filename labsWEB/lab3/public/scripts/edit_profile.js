import {banUser, editUser, getUser, toEditProfilePage} from "./client.js";

$(".ban_button").on("click", async function() {
    const userId = $(this).attr("id").split("ban_user#")[1]
    if (!isNaN(Number(userId))) {
        await banUser(userId)
    }
    location.reload()
})

$("#edit_profile_button_save").on("click", async function() {
    const prevId = $("#profile_id").text()

    const id = $("#edit_profile_id_input").val()
    const name = $("#edit_profile_name_input").val()
    const image_link = $("#edit_profile_img_link_input").val()
    const birth = $("#edit_profile_birth_input").val()
    const gender = $("#edit_profile_gender_select").val()
    const role = $("#edit_profile_role_select").val()
    const status = $("#edit_profile_status_select").val()
    const email = $("#edit_profile_email_input").val()

    const user = {
        "id": id,
        "name": name,
        "image_link": image_link,
        "birth": birth,
        "gender": gender,
        "role": role,
        "status": status,
        "email": email
    }
    await editUser(user, prevId)
    toEditProfilePage(user.id)
})

$("#edit_profile_button_revert").on("click", async function() {
    const prevId = $("#profile_id").text()
    const user = await getUser(prevId)

    $("#edit_profile_id_input").val(user.id)
    $("#edit_profile_name_input").val(user.name)
    $("#edit_profile_img_link_input").val(user.image_link)
    $("#edit_profile_birth_input").val(user.birth)
    $("#edit_profile_gender_select").val(user.gender)
    $("#edit_profile_role_select").val(user.role)
    $("#edit_profile_status_select").val(user.status)
    $("#edit_profile_email_input").val(user.email)
})
