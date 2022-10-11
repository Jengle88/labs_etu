function scriptStart() {
    const BookStatus = Object.freeze({
        IN_STOCK: "В наличии",
        UNAVAILABLE: "Занята",
        OVERDUE: "Просрочена",
        UNKNOWN: "Неизвестно"
    })
    const books = [
        {title: "Книга 1", author: "Автор 1", bookStatus: BookStatus.IN_STOCK},
        {title: "Книга 2", author: "Автор 2", bookStatus: BookStatus.UNAVAILABLE},
        {title: "Книга 3", author: "Автор 3", bookStatus: BookStatus.OVERDUE},
        {title: "Книга 4", author: "Автор 4", bookStatus: BookStatus.IN_STOCK},
    ]
    let listOfBooks = document.getElementById("list_of_books")

    for (let i = 0; i < books.length; i++) {
        let newBook = TableRowBook.createBookRow(books[i].title, books[i].author, books[i].bookStatus, function () { })
        listOfBooks.appendChild(newBook)
    }
}