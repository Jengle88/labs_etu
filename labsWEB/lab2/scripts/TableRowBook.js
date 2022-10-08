class TableRowBook {
    static #createBookTitleAndAuthorDiv(title, author) {
        let bookTitleAndAuthor = document.createElement("div")
        bookTitleAndAuthor.className = "book-title-and-author"
        let bookTitle = document.createElement("p")
        bookTitle.className = "book-title"
        bookTitle.innerText = title
        let bookAuthor = document.createElement("p")
        bookAuthor.className = "book-author"
        bookAuthor.innerText = author
        bookTitleAndAuthor.append(bookTitle, bookAuthor)
        return bookTitleAndAuthor;
    }

    static #createBookStatusAndActionsDiv(status, onclickAction) {
        let bookStatusAndActions = document.createElement("div")
        bookStatusAndActions.className = "book-status-and-actions"
        let bookStatus = document.createElement("p")
        bookStatus.className = "book-status"
        bookStatus.innerText = status
        let bookActionsDiv = document.createElement("div")
        bookActionsDiv.className = "book-actions"
        let addBookActionImg = document.createElement("img")
        addBookActionImg.src = "ic_add_book.png"
        addBookActionImg.className = "book-action-icon"
        addBookActionImg.onclick = onclickAction
        let removeBookActionImg = document.createElement("img")
        removeBookActionImg.src = "ic_remove_book.png"
        removeBookActionImg.className = "book-action-icon"
        removeBookActionImg.onclick = function () {

        }
        bookActionsDiv.append(addBookActionImg, removeBookActionImg)
        bookStatusAndActions.append(bookStatus, bookActionsDiv)
        return bookStatusAndActions
    }

    static createBookRow(title, author, status, onclickAction) {
        let newBook = document.createElement("div")
        newBook.className = "book-in-list-of-books"
        let bookTitleAndAuthor = TableRowBook.#createBookTitleAndAuthorDiv(title, author);
        let bookStatusAndActions = TableRowBook.#createBookStatusAndActionsDiv(status, onclickAction)
        newBook.append(bookTitleAndAuthor, bookStatusAndActions)
        return newBook
    }
}

