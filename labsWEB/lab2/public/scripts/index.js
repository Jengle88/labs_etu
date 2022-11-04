import {
    getBookById,
    returnBook,
    takeBook,
    toAddNewBookPage,
    toBookInfoPage,
    toIndexPage,
} from "./client.js";
import {Preprocessor} from "./Preprocessor.js";

// set id
const buttonAddNewBook = document.getElementById("start_add_new_book")
const mainTitle = document.getElementById("main_title")
const listOfBooksElem = document.getElementsByClassName("book-in-list-of-books")
const listOfBooks = Array.prototype.slice.call(listOfBooksElem)


// set listeners
buttonAddNewBook.addEventListener("click", toAddNewBookPage)
mainTitle.addEventListener("click", toIndexPage)

function updateBookCard(book, htmlBookCard) {
    htmlBookCard.getElementsByClassName("book-title")[0]
        .innerText = book.title
    htmlBookCard.getElementsByClassName("book-author")[0]
        .innerText = book.author
    htmlBookCard.getElementsByClassName("book-status")[0]
        .innerText = Preprocessor.statusToLocaleLang(book.status)
}

listOfBooks.forEach(htmlBookCard => {
    const id = htmlBookCard.id.split("book_in_list_of_books#")[1]
    document.getElementById(`book_action_take#${id}`)
        .addEventListener("click", async () => {
            if (Number(id)) {
                // FIXME заменить на подстановку пользователя
                await takeBook(Number(id), "Human1", "2022-12-3")
                let book = await getBookById(id)
                updateBookCard(book, htmlBookCard)
            }
        })
    document.getElementById(`book_action_return#${id}`)
        .addEventListener("click", async () => {
            if (Number(id)) {
                await returnBook(Number(id))
                let book = await getBookById(id)
                updateBookCard(book, htmlBookCard)
            }
        })
    document.getElementById(`book_title#${id}`)
        .addEventListener("click", () => {
            toBookInfoPage(id)
        })
})

