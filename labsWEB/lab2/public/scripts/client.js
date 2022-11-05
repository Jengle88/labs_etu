import {Preprocessor} from "./Preprocessor.js";

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
    let response = await fetch(URL + "/api/get_book/" + bookId.toString())
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

/**
 * @route PUT /api/remove_book
 * @desc Remove book to storage
 * @param bookId book id, which need to remove
 */
export async function removeBook(bookId) {
    let response = await fetch(URL + "/api/remove_book", {
        method: "DELETE",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({bookId: bookId})
    })
    let answer = await response.json()
    toIndexPage()
    return answer
}

/**
 * @desc Take book from storage
 * @param bookId book id, which need to remove
 * @param wasTakenBy nickname of reader
 * @param returnDate deadline for book return
 */
export async function takeBook(bookId, wasTakenBy, returnDate) {
    let book = await getBookById(bookId)
    if (book && book.status === Preprocessor.BookStatus.IN_STOCK) {
        book.was_taken_by = wasTakenBy
        book.return_date = returnDate
        book.status = Preprocessor.BookStatus.UNAVAILABLE
        editBook(book)
    } else {
        console.log("/api/takeBook: Book not found or already taken")
    }
}

/**
 * @desc Return book to storage
 * @param bookId book id, which need to remove
 */
export async function returnBook(bookId) {
    let book = await getBookById(bookId)
    if (book && (book.status === Preprocessor.BookStatus.UNAVAILABLE)) {
        book.was_taken_by = null
        book.return_date = null
        book.status = Preprocessor.BookStatus.IN_STOCK
        editBook(book)
    } else {
        console.log("/api/returnBook: book was not found or no one took it")
    }
}

export async function saveBookDataToStorage(book) {
    await addBook(book)
    toIndexPage()
}

export function cancelAddBookRequest() {
    toIndexPage()
}

export function actionWithCheckCurrUser(actionIfUserAuthorized, actionIfUserUnauthorized = () => {
    alert("Пользователь не авторизован")
}) {
    if (localStorage["current_user"] !== undefined && localStorage["current_user"].length !== 0)
        actionIfUserAuthorized()
    else
        actionIfUserUnauthorized()
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
