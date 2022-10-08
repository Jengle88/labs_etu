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
/*

                        // - const data = fs.readFileSync("./storage/data.json")
                        // - for(let book in data)
                        //   div.book-in-list-of-books(id="book_in_list_of_books")
                        //       div.book-title-and-author(id="book_title_and_author")
                        //           p.book-title(id="book_title") #{book.title}
                        //           p.book-author(id="book_author") #{book.author}
                        //       div.book-status-and-actions(id="book_status_and_actions")
                        //           p.book-status(id="book_status") #{book.status}
                        //           div.book-actions(id="book_actions")
                        //               img.book-action-icon(id="book_action_add", src="ic_add_book.png")
                        //               img.book-action-icon(id="book_action_remove", src="ic_remove_book.png")
 */