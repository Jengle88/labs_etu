const roles = Object.freeze({
    "admin": "Администратор",
    "user": "Пользователь",
})

const access = Object.freeze({
    "confirmed": "Подтверждён",
    "guest": "Гостевой доступ",
    "banned": "Заблокирован"
})

class StringPreprocessor {
    getUserRole(role) {
        if (role in roles)
            return roles[role]
        else
            return "Undefined"
    }

    getUserStatus(status) {
        if (status in access)
            return access[status]
        else
            return "Unconfirmed"
    }
}

const stringPreprocessor = new StringPreprocessor()
function localizeData(user) {
    user.role = stringPreprocessor.getUserRole(user.role)
    user.status = stringPreprocessor.getUserStatus(user.status)
    return user
}

module.exports.localizeData = localizeData