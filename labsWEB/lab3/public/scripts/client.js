const url = "https://localhost:3000"

/**
 * @route GET /
 * @desc Index page
 */
export function toIndexPage() {
    window.location.href = url + "/"
}
/**
 * @route GET /admin_panel
 * @desc Admin panel page
 */

export function toAdminPanelPage() {
    window.location.href = url + "/admin_panel"
}

/**
 * @route GET /profile/:userId
 * @param userId User ID
 * @desc Page with profile of user
 */
export function toProfilePage(userId) {
    window.location.href = url + `/profile/${userId}`
}

/**
 * @route GET /edit_profile/:userId
 * @param userId User ID
 * @desc Page with profile of user for editing
 */
export function toEditProfilePage(userId) {
    window.location.href = url + `/edit_profile/${userId}`
}