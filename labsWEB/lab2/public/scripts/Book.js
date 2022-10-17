export class Book {
    constructor(id = null, title = null, author = null, status = null, return_date = null) {
        this.id = id
        this.title = title
        this.author = author
        this.status = status
        this.return_date = return_date
    }
}