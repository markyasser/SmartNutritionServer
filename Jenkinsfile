pipeline {
    agent any

    environment {
        // Define any necessary environment variables here
        BUILD_DIR = 'build'
        DEPLOY_DIR = 'smart_nutrition_server'
    }

    stages {
        stage ('Install Crow'){
            sh 'git clone https://github.com/CrowCpp/Crow.git'
        }
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

        stage('Deploy') {
            steps {
                script {
                    // Ensure the deployment directory exists
                    sh "mkdir -p ${DEPLOY_DIR}"
                    
                    // Copy the built application to the deployment directory
                    sh "cp ${BUILD_DIR}/SmartNutritionServer ${DEPLOY_DIR}/"
                }
            }
        }

        stage('Run') {
            steps {
                script {
                    // Run the application
                    dir("${DEPLOY_DIR}") {
                        sh './SmartNutritionServer'
                    }
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
