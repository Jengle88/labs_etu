const url = "https://localhost:3000"

/**
 * @route GET /api/get_users
 * @description  Return users list
 */
export const getUsers = async () => {
    let response = await fetch(url + "/api/users/get_users")
    return await response.json()
}

/**
 * @route GET /api/users/get_user/:userId
 * @description  Return user by userId
 */
export async function getUser(userId) {
    let response = await fetch(url + `/api/users/get_user/${userId}`, {
        method: "GET"
    })
    return await response.json()
}

/**
 * @route GET /api/users/get_user_with_localize/:userId
 * @description  Return user with localize by userId
 */
export async function getUserWithLocalize(userId) {
    let response = await fetch(url + `/api/users/get_user_with_localize/${userId}`, {
        method: "GET"
    })
    return await response.json()
}

/**
 * @route GET /api/users/get_full_user_info/:userId
 * @param userId User ID
 * @description Get user info + friends + user posts + friends posts
 */
export async function getFullUserInfo(userId) {
    let response = await fetch(url + `/api/users/get_full_user_info/${userId}`, {
        method: "GET"
    })
    return await response.json()
}
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
 * @route PUT /api/users/edit_user/:userId
 * @param editedUser
 * @param userId User ID
 * @description Edit user info in database
 */
export async function editUser(editedUser, userId) {
    let response = await fetch(url + `/api/users/edit_user/${userId}`, {
        method: "PUT",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({editedUser})
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