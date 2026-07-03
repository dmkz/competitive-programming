from pathlib import Path


TITLE = "# Лекция 1. Массивы, сортировки, бинарный поиск в отсортированном массиве"
PART_FILES = [
    "README1-arrays-and-lists.md",
    "README2-processing.md",
]
NOTICE = """<!-- Этот файл собран автоматически из README1-arrays-and-lists.md и README2-processing.md. -->
<!-- Для обновления запустите: python build-readme.py -->"""


def read_part(path: Path) -> str:
    return path.read_text(encoding="utf-8").strip()


def main() -> None:
    root = Path(__file__).resolve().parent
    parts = [read_part(root / file_name) for file_name in PART_FILES]
    readme_text = "\n\n".join([NOTICE, TITLE, *parts]) + "\n"

    with (root / "README.md").open("w", encoding="utf-8", newline="\n") as output_file:
        output_file.write(readme_text)


if __name__ == "__main__":
    main()