const URL = `http://localhost:3000`

/**
 * @route GET /api/get_books
 * @desc Return array of books
 */
export async function getBooks() {
    let response = await fetch(URL + "/api/get_books")
    return await response.json()
}

/**
 * @route GET /api/get_book/:book_id
 * @desc Return available ID for new book
 * @param bookId id (Number) of the required book
 */
export async function getBookById(bookId) {
    let response = await fetch(URL + "/api/get_book" + bookId.toString())
    return await response.json()
}

/**
 * @route POST /api/add_book
 * @desc Add new book to storage
 * @param book new book
 */
export async function addBook(book) {
    let response = await fetch(URL + "/api/add_book", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({book})
    })
    return await response.json()
}

/**
 * @route PUT /api/add_book
 * @desc Edit book to storage
 * @param editedBook book for save to storage
 */
export async function editBook(editedBook) {
    let response = await fetch(URL + "/api/edit_book", {
        method: "PUT",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({editedBook})
    })
    return await response.json()
}

export async function saveBookDataToStorage(book) {
    await addBook(book)
    toIndexPage()
}

export function cancelAddBookRequest() {
    toIndexPage()
}

export function toIndexPage() {
    window.location.href = URL + "/"
}

export function toAddNewBookPage() {
    window.location.href = URL + "/add_new_book"
}

export function toBookInfoPage(id) {
    window.location.href = URL + `/book_info/${id}`
}
