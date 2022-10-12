import {
    Preprocessor
} from "./Preprocessor.js";

import {
    TableRowBook
} from "./TableRowBook.js"

export const addBook = () => {
    const book = new Object({title: "Книга 1", author: "Автор 1", bookStatus: Preprocessor.BookStatus.IN_STOCK})
    let listOfBooks = document.getElementById("list_of_books")
    let newBook = TableRowBook.createBookRow(book.title, book.author, Preprocessor.fromLocaleStatus(book.bookStatus), function () { })
    listOfBooks.appendChild(newBook)
}
