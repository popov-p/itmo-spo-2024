import subprocess

def run_command(command):
    try:
        result = subprocess.run(command, shell=True, text=True, capture_output=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        print(f"Ошибка при выполнении команды '{command}': {e.stderr}")
        return None

USER_LOGIN = "u467160"
USER_PASSWORD = "55d9fe6c-da4a-4f5a-94a2-cdec8c4e69c1"
