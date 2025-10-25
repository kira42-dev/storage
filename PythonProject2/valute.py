# currency_parser.py
import urllib.request
import csv
import json
from datetime import datetime
import sqlite3
from typing import Dict, Any, List, Optional


class CurrencyParser:
    def __init__(self, base_url: str = "https://www.cbr-xml-daily.ru/daily_json.js"):
        self.base_url = base_url

    def get_currency_rates(self) -> Optional[Dict[str, Any]]:
        """Получение курсов валют с ЦБ РФ"""
        try:
            with urllib.request.urlopen(self.base_url, timeout=10) as response:
                data = json.loads(response.read().decode('utf-8'))
                return data['Valute']
        except Exception as e:
            print(f"Ошибка при получении данных: {e}")
            return None

    def save_to_csv(self, currencies: Dict[str, Any], filename: str = 'currency_rates.csv') -> bool:
        """Сохранение в CSV"""
        try:
            with open(filename, 'w', newline='', encoding='utf-8') as csvfile:
                fieldnames = ['CharCode', 'Name', 'Value', 'Previous', 'Timestamp']
                writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

                writer.writeheader()
                for code, currency in currencies.items():
                    writer.writerow({
                        'CharCode': code,
                        'Name': currency['Name'],
                        'Value': currency['Value'],
                        'Previous': currency['Previous'],
                        'Timestamp': datetime.now().isoformat()
                    })
            print(f"Данные сохранены в {filename}")
            return True
        except Exception as e:
            print(f"Ошибка при сохранении в CSV: {e}")
            return False

    def save_to_sqlite(self, currencies: Dict[str, Any], db_name: str = 'currency.db') -> bool:
        """Сохранение в SQLite"""
        conn = None
        try:
            conn = sqlite3.connect(db_name)
            c = conn.cursor()

            c.execute('''
                CREATE TABLE IF NOT EXISTS currency_rates (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    char_code TEXT NOT NULL,
                    name TEXT NOT NULL,
                    value REAL NOT NULL,
                    previous REAL NOT NULL,
                    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
                )
            ''')

            for code, currency in currencies.items():
                c.execute('''
                    INSERT INTO currency_rates (char_code, name, value, previous)
                    VALUES (?, ?, ?, ?)
                ''', (code, currency['Name'], currency['Value'], currency['Previous']))

            conn.commit()
            print(f"Данные сохранены в базу {db_name}")
            return True
        except sqlite3.Error as e:
            print(f"Ошибка базы данных: {e}")
            return False
        finally:
            if conn:
                conn.close()

    def analyze_changes(self, currencies: Dict[str, Any]) -> List[Dict[str, Any]]:
        """Анализ изменений курсов"""
        changes = []
        for code, currency in currencies.items():
            current_value = currency['Value']
            previous_value = currency['Previous']

            if previous_value == 0:
                percent_change = 0.0
            else:
                percent_change = ((current_value - previous_value) / previous_value) * 100

            change = current_value - previous_value

            changes.append({
                'currency': code,
                'name': currency['Name'],
                'change': round(change, 4),
                'percent_change': round(percent_change, 2),
                'current_value': current_value,
                'previous_value': previous_value
            })

        changes.sort(key=lambda x: abs(x['percent_change']), reverse=True)
        return changes[:5]

    def print_top_changes(self, top_changes: List[Dict[str, Any]]) -> None:
        """Вывод топ-5 изменений"""
        print("\nТоп-5 изменений курсов:")
        print("-" * 60)
        for change in top_changes:
            trend = "↑" if change['change'] > 0 else "↓"
            print(f"{change['currency']} ({change['name']}): {change['percent_change']:+.2f}% {trend}")
            print(f"  Текущий: {change['current_value']:.4f} | Предыдущий: {change['previous_value']:.4f}")


def main():
    parser = CurrencyParser()
    currencies = parser.get_currency_rates()

    if currencies:
        parser.save_to_csv(currencies)
        parser.save_to_sqlite(currencies)

        top_changes = parser.analyze_changes(currencies)
        parser.print_top_changes(top_changes)
    else:
        print("Не удалось получить данные о курсах валют")


if __name__ == '__main__':
    main()