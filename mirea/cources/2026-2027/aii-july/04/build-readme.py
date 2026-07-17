import re
from pathlib import Path


TITLE = "# Лекция 4. Префиксные суммы, запросы на отрезках и префиксный подход. Разностный массив"
PART_DIRS = [
    "Part-01-Prefix-sums",
    "Part-02-Prefix-and-suffix-approach",
    "Part-03-Difference-array",
]
NOTICE = """<!-- Этот файл собран автоматически из README.md внутри Part-01-Prefix-sums, Part-02-Prefix-and-suffix-approach и Part-03-Difference-array. -->
<!-- Для обновления запустите: python build-readme.py -->"""
LINK_RE = re.compile(r"\[([^\]]+)\]\(([^)]+)\)")


def rewrite_relative_links(text: str, part_dir_name: str) -> str:
    def replace(match: re.Match[str]) -> str:
        label, target = match.groups()
        if target.startswith(("http://", "https://", "#", "mailto:", "/")):
            return match.group(0)
        return f"[{label}]({part_dir_name}/{target})"

    return LINK_RE.sub(replace, text)


def read_part(path: Path) -> str:
    text = path.read_text(encoding="utf-8").strip()
    return rewrite_relative_links(text, path.parent.name)


def main() -> None:
    root = Path(__file__).resolve().parent
    parts = [read_part(root / part_dir / "README.md") for part_dir in PART_DIRS]
    readme_text = "\n\n".join([NOTICE, TITLE, *parts]) + "\n"

    with (root / "README.md").open("w", encoding="utf-8", newline="\n") as output_file:
        output_file.write(readme_text)


if __name__ == "__main__":
    main()