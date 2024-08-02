pipeline {
    agent any

    environment {
        // Define any necessary environment variables here
        BUILD_DIR = 'build'
        DEPLOY_DIR = 'smart_nutrition_server'
    }

    stages {
        stage('Build') {
            steps {
                script {
                    // Ensure the build directory is clean
                    sh 'rm -rf ${BUILD_DIR}'
                    
                    // Create and navigate to the build directory
                    sh 'mkdir -p ${BUILD_DIR}'
                    dir("${BUILD_DIR}") {
                        // Run CMake to configure the build
                        sh 'cmake ..'
                        
                        // Build the project
                        sh 'make -j$(nproc)'  // Use all available cores for faster build
                    }
                }
            }
        }

        stage('Run') {
            steps {
                script {
                    // Terminate any existing instances of the application
                    sh '''
                        # Find PIDs listening on port 4000 and kill them
                        pids=$(sudo lsof -t -i :4000)
                        if [ ! -z "$pids" ]; then
                            sudo kill -9 $pids
                        fi
                    '''

                    // Start the application in the background
                    sh "nohup ./${BUILD_DIR}/SmartNutritionServer > /dev/null 2>&1 &"
                }
            }
        }
    }

    post {
        success {
            echo 'Build and deployment completed successfully.'
        }

        failure {
            echo 'Build or deployment failed.'
        }
    }
}
