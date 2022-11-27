const url = "https://localhost:3000"

/**
 * @route DELETE /api/posts/delete_post/:postId
 * @param postId Post ID
 * @description Delete post from database
 */
export async function deletePost(postId) {
    let response = await fetch(url + `/api/posts/delete_post/${postId}`, {
        method: "DELETE"
    })
    return await response.json()
}

/**
 * @route DELETE /api/users/delete_user/:userId
 * @param userId User ID
 * @description Delete user info from database
 */
export async function deleteUser(userId) {
    let response = await fetch(url + `/api/users/delete_user/${userId}`, {
        method: "DELETE"
    })
    return await response.json()
}

/**
 * @route PUT /api/users/edit_user/:userId
 * @param user Edited user
 * @param userId User ID
 * @description Edit user info in database
 */
export async function editUser(user, userId) {
    let response = await fetch(url + `/api/users/edit_user/${userId}`, {
        method: "PUT",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({user})
    })
    return await response.json()
}

/**
 * @route PUT /api/users/ban_user/:userId
 * @param userId User ID
 * @description Ban user in database
 */
export async function banUser(userId) {
    let response = await fetch(url + `/api/users/ban_user/${userId}`, {
        method: "PUT"
    })
    return await response.json()
}

/**
 * @route GET /
 * @description Index page
 */
export function toIndexPage() {
    window.location.href = url + "/"
}
/**
 * @route GET /admin_panel
 * @description Admin panel page
 */
export function toAdminPanelPage() {
    window.location.href = url + "/admin_panel"
}

/**
 * @route GET /profile/:userId
 * @param userId User ID
 * @description Page with profile of user
 */
export function toProfilePage(userId) {
    window.location.href = url + `/profile/${userId}`
}

/**
 * @route GET /edit_profile/:userId
 * @param userId User ID
 * @description Page with profile of user for editing
 */
export function toEditProfilePage(userId) {
    window.location.href = url + `/edit_profile/${userId}`
}