import {
    Preprocessor
} from "./Preprocessor.js";

const URL = `http://localhost:3000`

// API

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
    let bookMock = new Object({title: "Книга 1", author: "Автор 1", status: Preprocessor.BookStatus.IN_STOCK, return_date: "02.10.2022"})
    let response = await fetch(URL + "/api/add_book", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({bookMock})
    })

    let result = await response.json()
    toIndexPage()

    return result
}

export function toIndexPage() {
    window.location.href = URL + "/"
}

export function toAddNewBookPage() {
    window.location.href = URL + "/add_new_book"
}
