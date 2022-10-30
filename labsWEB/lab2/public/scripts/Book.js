export class Book {
    constructor(id = -1,
                title = null,
                author = null,
                status = null,
                release_date = null,
                was_taken_by = null,
                return_date = null
    ) {
        this.id = id
        this.title = this.stringIfNull(title)
        this.author = this.stringIfNull(author)
        this.status = this.stringIfNull(status)
        this.release_date = this.dateIfNull(release_date)
        this.was_taken_by = was_taken_by
        this.return_date = return_date
    }
    stringIfNull(value) {
        if (value === null)
            return "Неизвестно"
        else
            return value
    }

    dateIfNull(value) {
        if (value === null)
            return "01.01.1970"
        else
            return value
    }

}