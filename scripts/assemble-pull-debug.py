#!/usr/bin/env python3
import re
import sys

from utils.run_command import run_command, USER_LOGIN, USER_PASSWORD

assemble_debug_command = (
    f"mono ./RemoteTasks/Portable.RemoteTasks.Manager.exe "
    f"-ul \"{USER_LOGIN}\" "
    f"-up \"{USER_PASSWORD}\" "
    f"-w -s AssembleDebug definitionFile ./arch/arch-popov-v24.target.pdsl "
    f"archName popov-v24 asmListing ./examples/asm-gen/listing.txt sourcesDir ."
)

assemble_debug_output = run_command(assemble_debug_command)
if not assemble_debug_output:
    print("AssembleDebug завершился с ошибкой. Скрипт завершён.")
    sys.exit(1)

print("Вывод AssembleDebug:\n", assemble_debug_output)


match = re.search(r"[a-f0-9\-]{36}", assemble_debug_output)
if not match:
    print("Не удалось извлечь ID задачи. Проверьте вывод первой команды.")
    sys.exit(1)

task_id = match.group(0)
print(f"Извлечённый ID задачи: {task_id}")

pull_binary_command = (
    f"mono ./RemoteTasks/Portable.RemoteTasks.Manager.exe "
    f"-ul \"{USER_LOGIN}\" "
    f"-up \"{USER_PASSWORD}\" "
    f"-g {task_id} -r out.ptptb -o ./examples/asm-gen/hw.ptptb"
)

pull_binary_output = run_command(pull_binary_command)
if pull_binary_output is None:
    print("Pull Binary завершился с ошибкой.")
    sys.exit(1)

if pull_binary_output.strip() == "":
    print("Pull Binary выполнен успешно.")
else:
    print("Вывод Pull Binary:\n", pull_binary_output)
