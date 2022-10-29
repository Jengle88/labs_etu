import {
    saveBookDataToStorage,
    cancelAddBookRequest,
    toIndexPage,
} from "./client.js";
import {Preprocessor} from "./Preprocessor.js";
import {Book} from "./Book.js"

// set id
const buttonBookSave = document.getElementById("add_book_book_save")
const buttonBookCancel = document.getElementById("add_book_book_cancel")
const inputBookTitle = document.getElementById("abb_book_new_book_title")
const inputFIOAuthor = document.getElementById("abb_book_new_book_author")
const inputReleaseDate = document.getElementById("abb_book_new_book_release_date")
const mainTitle = document.getElementById("main_title")

// set listeners
buttonBookSave.addEventListener("click", saveBookData)
buttonBookCancel.addEventListener("click", cancelAddBookRequest)
mainTitle.addEventListener("click", toIndexPage)

// clear fields
inputBookTitle.value = ""
inputFIOAuthor.value = ""


export async function saveBookData() {
    let bookTitle = inputBookTitle.value
    let fioAuthor = inputFIOAuthor.value
    let releaseDate = inputReleaseDate.value
    let book = new Book(null, bookTitle, fioAuthor, Preprocessor.BookStatus.IN_STOCK, releaseDate)
    await saveBookDataToStorage(book)
}