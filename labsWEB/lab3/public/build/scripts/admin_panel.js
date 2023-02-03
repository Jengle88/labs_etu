import {banUser, getUsers} from "./client.js";

$(document).ready(async function () {
    const users = await getUsers()
    users.forEach(user => {
        let userHtml = `<tr>\n
                            <th class=\"admin_panel_table_user_name\" scope=\"row\">${user.name}</th>\n
                            <td class=\"admin_panel_table_birth_date\" scope=\"\">${user.birth}</td>\n
                            <td class=\"admin_panel_table_gender\" scope=\"\">${user.gender}</td>\n
                            <td class=\"admin_panel_table_role\" scope=\"\">${user.role}</td>\n
                            <td class=\"admin_panel_table_status\" scope=\"\">${user.status}</td>\n
                            <td class=\"admin_panel_table_email\" scope=\"\">${user.email}</td>\n
                            <td class=\"admin_panel_table_buttons\" scope=\"\"><a href=\"/profile/${user.id}\">\n
                                <button class=\"button-primary action-button\" type=\"button\">Профиль</button>\n
                            </a><a href=\"/edit_profile/${user.id}\">\n
                                <button class=\"button-warning action-button\" type=\"button\">Редактировать</button>\n
                            </a>\n
                                <button class=\"button-danger action-button ban_button\" type=\"button\" id=\"ban_user#${user.id}\">\n
                                    Заблокировать\n
                                </button>\n
                            </td>\n
                        </tr>`
        $("#table_body").append($(userHtml))
    })

    $(".ban_button").on("click", async function () {
        const userId = $(this).attr("id").split("ban_user#")[1]
        if (!isNaN(Number(userId))) {
            await banUser(userId)
        }
        location.reload()
    })
})


